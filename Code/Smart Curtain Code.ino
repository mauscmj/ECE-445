
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>

const char* ssid     = "501Healey21";
const char* password = "fancywindow523";

const int identity_led = 2;
const int led_gpio = 23;
const int FWD = 5; // d0
const int REV = 18; // d1
const int LED = 13; // d2
const int BUTTON = 16; //d3
const int PHOTO = 39; // Analog in 
const int ENCODER1 = 32;
const int ENCODER2 = 33;
int curr_loc = 0;
int sensorValue = 0;

const bool switchOn  = false;     // using INPUT_PULLUP
const bool switchOff = true;

bool lastState   = switchOff;
bool newState    = switchOff;
bool toggleState = false;

extern "C" {
#include "homeintegration.h"
}
homekit_service_t* hapservice = {0};
String pair_file_name = "/pair.dat";
// homekit_characteristic_t * ch_current_pos= NULL;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(REV,OUTPUT);
  pinMode(FWD,OUTPUT);

  // Mount SPIFFS file system
  if (!SPIFFS.begin(true)) {
    Serial.print("SPIFFS mount failed");
  }

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(led_gpio, OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(PHOTO,INPUT);
  pinMode(ENCODER1,INPUT);
  pinMode(ENCODER2,INPUT);
  
  ///setup identity gpio
  hap_set_identity_gpio(identity_led);    //identity_led=2 will blink on identity

  /// now will setup homekit device

  //this is for custom storage usage
  // In given example we are using \pair.dat file in our SPIFFS system
  //see implementation below
  init_hap_storage();
  set_callback_storage_change(storage_changed);

  /// We will use for this example only one accessory (possible to use a several on the same ESP)
  //Our accessory type is light bulb, Apple interface will proper show that
  hap_setbase_accessorytype(homekit_accessory_category_window_covering);

  /// init base properties
  hap_initbase_accessory_service("hosta", "Yurik72a", "01", "EspHapLed2", "2.0");
  //we will add only one light bulb service and keep pointer for nest using
  hapservice = hap_add_windowcovering_service("Led", led_callback, (void*)&led_gpio);
  // ch_current_pos= homekit_service_characteristic_by_type(hapservice, HOMEKIT_CHARACTERISTIC_CURRENT_POSITION);
  // INIT_CHARACHTERISTIC_VAL(int,ch_current_pos,100);

  //and finally init HAP
  hap_init_homekit_server();

  attachInterrupt(digitalPinToInterrupt(ENCODER1), encoder_isr, CHANGE);
  loop();
}

void loop() {
  // put your main code here, to run repeatedly:
  Flip();
  sensorValue = analogRead(PHOTO);
 // Serial.println("sensorValue: " + String(sensorValue));
  if(toggleState == false) {
    if(curr_loc >= -450) {
      set_motor(0);
      toggleState = true;
    }
    else{
      set_motor(100);
      toggleState = true;
    }
  }
  if(curr_loc >= -75 && sensorValue <= 500) {
    // Serial.println("sensorValue: " + String(sensorValue));
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  delay(50);
}

void init_hap_storage() {
  Serial.print("init_hap_storage");
  File fsDAT = SPIFFS.open(pair_file_name, "r");
  if (!fsDAT) {
    Serial.println("Failed to read file pair.dat");
    return;
  }
  int size = hap_get_storage_size_ex();
  char* buf = new char[size];
  memset(buf, 0xff, size);
  int readed = fsDAT.readBytes(buf, size);
  Serial.print("Readed bytes ->");
  Serial.println(readed);
  hap_init_storage_ex(buf, size);
  fsDAT.close();
  delete []buf;
}

void storage_changed(char * szstorage, int size) {
  SPIFFS.remove(pair_file_name);
  File fsDAT = SPIFFS.open(pair_file_name, "w+");
  if (!fsDAT) {
    Serial.println("Failed to open pair.dat");
    return;
  }
  fsDAT.write((uint8_t*)szstorage, size);
  fsDAT.close();
}

//can be used for any logic, it will automatically inform Apple Home app about state changes
void set_motor(int val) {
  Serial.println("set_led");
  Rotate_motor(100 - val);
  //we need notify apple about changes
  if (hapservice) {
    Serial.println("notify hap");
    //getting on/off characteristic
    // HAP_NOTIFY_CHANGES(int, ch_current_pos, val,0)
    homekit_characteristic_t * ch = homekit_service_characteristic_by_type(hapservice, HOMEKIT_CHARACTERISTIC_ON);
    if (ch) {
      Serial.println("found characteristic");
      if (ch->value.int_value != val) { //will notify only if different
        ch->value.int_value = val;
        homekit_characteristic_notify(ch, ch->value);
      }
    }
  }
}

void Rotate_motor(int target_location) {
  Serial.println(String(curr_loc) + " before");
  if(curr_loc > -900 * 0.01 * target_location) {
    while(curr_loc >= -900 * 0.01 * target_location ) {
      analogWrite(FWD, 0);    // rotate down
      analogWrite(REV, 200);
    }
    // toggleState = true;
  }
  else if(curr_loc < -900 * 0.01 * target_location) {
      while(curr_loc <= -900 * 0.01 * target_location) {
      analogWrite(FWD, 255);
      analogWrite(REV, 0);
    }
    // toggleState = true;
  }
  analogWrite(FWD, 0);
  analogWrite(REV, 0);
}

void encoder_isr() {
  // Reading the current state of encoder A and B
  int A = digitalRead(ENCODER1);
  int B = digitalRead(ENCODER2);
  // If the state of A changed, it means the encoder has been rotated
  if ((A == HIGH) != (B == LOW)) {
    curr_loc--;
  } else {
    curr_loc++;
  }
}

void Flip() {
  newState = digitalRead(BUTTON);

  if( lastState != newState ) // state changed
  {
    delay(5);
    lastState = newState;
    
    // push on, push off
    if( newState == switchOn && toggleState == false )
    {
      toggleState = true;
    //  Serial.println( F ( "Switched ON" ) );
    }
    else if( newState == switchOn && toggleState == true )
    {
      toggleState = false;
     // Serial.println( F ( "Switched OFF" ) );
    }
  }
}

void led_callback(homekit_characteristic_t *ch, homekit_value_t value, void *context) {
  Serial.println("led_callback");
  Serial.println(value.int_value);
  set_motor(ch->value.int_value);
}