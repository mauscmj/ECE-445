/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2021-02-05
 *      Author: cooper @ makesmart.net
 *      Thank you for this great library!
 *      
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void window_covering_identify(homekit_value_t _value) {
  printf("Curtain identify\n");
}


// characteristics of the lock-mechanism
// format: uint8_t // 0 is unsecured // 1 is secured

homekit_characteristic_t cha_lock_current_state = HOMEKIT_CHARACTERISTIC_(CURRENT_POSITION, 1);
homekit_characteristic_t cha_lock_target_state = HOMEKIT_CHARACTERISTIC_(TARGET_POSITION, 1);

homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Window blind");

homekit_accessory_t *accessories[] = {
     HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_window_covering, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Window blind"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "MNK"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "001"),
            HOMEKIT_CHARACTERISTIC(MODEL, "MyCurtain"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.1"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, window_covering_identify),
            NULL
        }),
    HOMEKIT_SERVICE(WINDOW_COVERING, .primary=true, .characteristics=(homekit_characteristic_t*[]){
      HOMEKIT_CHARACTERISTIC(NAME, "Window blind"),
      &cha_lock_current_state,
      &cha_lock_target_state,
      &cha_name,
      NULL
    }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "123-45-678"
};
