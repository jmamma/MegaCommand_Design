//MegaCommand OLED Display Test Firmware
//Version 1.0
//Author: Justin Mammarella
//Date: March 2019
//Description: This firmware is used to test the MegaCommand OLED display.
//             The display should turn completely white for 2 seconds, the completely black for 2 seconds.
//             There should be no flashing or dead pixels.
//             Slight tearing might be observed.
//Notes:       This firmware uses the MegaCommand Core

#include "OLED.h"

void setup() {
   oled_display.begin();
   oled_display.clearDisplay();
   oled_display.invertDisplay(0);
   oled_display.setRotation(2);
  
   while (1) {
   oled_display.fillRect(0,0, 128,32, WHITE);
   oled_display.display();
   delay(2000);
   oled_display.fillRect(0,0, 128,32, BLACK);
   oled_display.display();
   delay(2000);

   }
}

void loop() {
  // put your main code here, to run repeatedly:

}
