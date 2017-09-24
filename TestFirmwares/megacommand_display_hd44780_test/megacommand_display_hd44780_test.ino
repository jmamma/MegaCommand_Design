//MegaCommand HD44780 LCD test
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test HD44780 16 x 2 LCD.
//             Run this firmware by uploading to the MegaCommand. The display should read "Display Okay!"
//Notes:       This firmware uses the Arduino Core.


#include <LiquidCrystal.h>
#define ADC0 97
#define ADC1 96
#define ADC2 95
#define ADC3 94

LiquidCrystal lcd(46, 45, A0, A1, A2, A3);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Display Okay!");

}
void loop() {

}
