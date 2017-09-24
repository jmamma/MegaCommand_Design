//MegaCommand LED test firmare.
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test the 2 LEDs on the MegaCommand Hardware
//             Run this firmware by uploading to the MegaCommand. You should see LED1 flash, then LED2 flash repeatedly. If not, check the LED orientation
//Notes:       This firmware uses the Arduino Core.

#define LED1_PIN PL3
#define LED2_PIN PL2

void setup() {
 
pinMode(LED1_PIN, OUTPUT);
pinMode(LED2_PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(LED1_PIN, HIGH);
 digitalWrite(LED2_PIN, LOW);
  delay(1000);    
    digitalWrite(LED1_PIN, LOW); 
              
   digitalWrite(LED2_PIN, HIGH);
  delay(1000);   
}
