# Vinay's Notes

## Contents

- [2/6/2023](#project-proposal-notes)
- [2/13/2023](#design-doc-meeting-notes)
- [2/27/2023](#design-review-notes)
- [3/8/2023](#post-design-review-notes)
- [3/27/2023](#demo-board-design-notes)
- [4/3/2023](#3d-printing-motor-part)
- [4/12/2023](#2nd-round-pcb-test)
- [4/13/2023](#breadboarding-circuit-and-programming-microcontroller)
- [4/16/2023](#testing-and-verification)
- [4/17/2023](#mock-demo)
- [4/24/2023](#pcb-integration-and-final-demo)
- [5/1/2023](#final-presentation)

## Project Proposal Notes
List of ideas that we have brainstormed:
- Smart Fridge
- Smart Mailbox
- Smart Humidifier
- Cooler that follows you
- Guitar Amp
- Auto inflating tire system
- object following camera stand
- Smart tv remote
- Guitar Auto Tuner
- Smart Stove
- Smart Curtains/blinds
- Auto Gear Shifter for Bicycle
- Smart Speaker System

The idea we decided on doing is "Cooler that follows you". Essentially a cooler that tracks its owner while moving on a cart. It also cools its drinks and tells owner when the cooler is at capacity

UPDATE: The "Cooler that follows you" idea got shut down by TA after doing initial rough proposal. We initially thought we could use an Arduino but the professor said it is not allowed and we must use a microprocessor on a PCB. The professor explained it would be too complicated to get the cooler to follow the owner with any resemeblance of a self driving cart. 

UPDATE: We are now pivoting to "Smart Curtains". Our initial proposal involves implementing a curtain that can open and close with a motor and can be controlled over wifi via HomeKit.

UPDATE: Smart Curtains got **approved** by TA under one condition: that we add a feature where we can detect the brightness level outside the window and if it is too dark (e.g. it's winter, cloudy, etc.) our system should include a string of LEDs around the window that will illuminate to provide more light.

Some initial sketches of our Smart Curtains Project:

![Drawing of Idea](initialsketch1.png)
![Drawing of Idea](initialsketch2.png)

## Design Doc Meeting Notes
For the design doc on top of the proposal we need to add:
- R & V Tables
- Circuit Diagrams
- Labor costs
- Part Costs
- Grand total cost
- Time Table/Schedule
- Hardware Design Choices Blurb
- Software Design Choices Blurb
- Make block diagram more specific (from TA)
- Physical Design Blurb and Physical Design CAD

My job: 
- R&V Tables
- Labor Costs
- Part Costs
- Overleaf Formatting
- Time Table/Scheduling
- Physical Design Blurb
- Physical Design CAD

Software using for CAD: Tinkerblocks

UPDATE: Tinkerblocks is a very tedious software. Similar to scratch programming but for CAD. Switching to a better software.

UPDATE: CAD is done. Using gear system is TBD based on if we get a motor with high torque.

UPDATE: Switching to 9V circuit wall mount instead of battery powered LiPo 5V circuit. The heavier components of our circuit are more common in 9V+ so it makes more sense.

UPDATE: We have decided to use ESP8266 as our microcontroller chip.

Some Images of Physical Design CAD:
![Physical Design](frontview.jpg)
![Physical Design](backview.jpg)

## Design Review Notes

Note: 100mmx100mm PCB is the max size pcb we can order

Note: make sure to take a look at the CHARM System design doc for reference (from TA)

Note: Keep in mind the sound of the motor when curtain moves up and down. If the purpose of the smart blind is to wake someone up with natural light as opposed to a loud alarm, then make sure the motor itself doesnt make enough sound to wake someone up.

Note: Make block diagram even more detailed. Have lines be specific and change color code to Labeled lines. Keep a legend for the lines as well.

Note: Cannot add things ordered from Amazon to budget. They will have to be out of pocket. Only things that can be on the school budget are Digikey orders and PCB orders.

## Post Design Review Notes

These are the notes right before our first PCB order

Note: Space out connectors on PCB board

Note: Space out microcontroller

Note: Check orientation of resistors and capicitors

Note: Order digikey parts soon and double the amount of parts for spares

Note: Check current of motor so that it doesn't reset pins

Note: Get motor with encoder down the road to make curtain movement more precise.

Note: (TWEAKS TO DESIGN DOC) Safety concerns other than privacy. Add thermal safety blurb. Be aware of noise of motor.

Note: Replace brightness with "ambient" bigness or "indoor" brightness

Note: Swap out controller and check it doesn't overcurrent the motor. Then test with a motor.

Note: Separate pcb and motor enclosure for simplicity and safety.

Note: Look into buying lightweight curtain material.

UPDATE: We are switching from ESP8266 to ESP32 for more pins

Note: We can generate PWM with code, no need for hardware.

Note: We can't use the devkit ESP32.

## Demo Board Design Notes

Quick Lowe's Run in preparation for assembling the board:
- Hot glue gun
- M3-.50x6 screws
- Flat washers #8
- Flat Phillips with Nuts #8-32 x 1/2 in
- Box Nails 4D X 1 1/2"
- Nuts #8-32
- 8 inch Assorted Cable ties
- foam boards 8 pcs

Note: window roller has arrived, will begin testing a demo setup.

Note: Idea for demo board assembly; I am going to use a 3x2.5 foot wood board for the curtain mount.

Note: I need something that will hold the curtain up and let it hang from the top.

Note: I decided to use a metal L piece with holes in it for mounting the curtain with screws.

Note: This idea works but I am struggling to attach the L piece to the thick wood piece I bought without a Drill!

Note: I am going to hammer but itll take me a while.

UPDATE: Everything is attached and looks pretty good! The excess nail poking out the back of the board I have bent into board and hotglued to the board for safety purposes.

The following is an image of the setup:

![Demo Board Setup](boardsetup.jpg)

Note: Other stuff accomplished with Max include: testing LED strip with 9V. 

The following is an image of testing LEDS:
![LED test](led_test.jpg)

Note: Unfortunately PCB is not working gotta wait for next round.


## 3D Printing Motor Part Notes

Note: Spent the day at Lowes trying to figure out a way to get the motor to spin the curtain through the curtains gear hole. Couldn't come up with anything so I will have to CAD and 3d print a part for it.

Note: Side quest, we are testing more parts. We are supposed to get our next PCB order since the first one didnt work. We have decided in the meantime lets Breadboard an LED circuit!

Note: breadboard task failed... For some reason the 5V signal wont cause MOSFET Drain to power the LED. 

Note: LED is just flickering and not actually switching with correct logic using the ESP8266 as a testing devkit.

Note: We figure the MOSFET is faulty. We will test BJT next.

Note: BJT works for a moment then stopped working. I think the board is fried.

UPDATE: 3d printed part has arrived. I ordered 9 of them since the measurements were very small and I couldn't run the risk of having the printer glitch and be slightly off.

Note: Used a #8-32 Nut and attached one of the pieces to the motor after clearing all the plastic gunk that was still in the hole.

Note: Part fits pretty well into the gear hole and effectively rolls/unrolls the curtain just by twisting the curtain with the motor manually.

Note: The motors static friction is surprisingly strong and can hold the curtain up pretty well.

![Motor piece](motor_attachment.jpg)
![Motor mount](motor_mounted.jpg)
![Motor piece](piece.gif)

## 2nd round PCB test

Note: ESP32 soldered chip on PCB not working, possible bad connections?

Note: Added solder to power connection and now receiving power, but unable to program!

Note: Pins for flashing not soldered well, resulting in non-responsive ESP32

Note: Photo resistor voltage remains constant, regardless of lighting

Note: Need to change resistor values and test on breadboard

Note: Motor controller test unsuccessful, voltage reading across FWD and REV but no motor turn

Note: MOSFET circuit for LED not working, even when gate is high

Note: Consider switching from common source to common drain on breadboard

Note: New plan is to use ESP8266 and breadboard for demo, aim to get it working on breadboard.

## Breadboarding Circuit and Programming Microcontroller

Note:
