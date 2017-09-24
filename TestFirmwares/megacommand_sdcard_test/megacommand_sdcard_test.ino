//MegaCommand SDCard test
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test SDCard breakout board.
//             Run this firmware by uploading to the MegaCommand. The frmware will write a file called test.txt to the SDCard.
//             View the serial monitor at 9600bps to see the test results.
//Notes:       This firmware uses the Arduino Core.
//             The SDCard needs to be formatted to FAT32.


#include <SD.h>

File myFile;

void setup()
{
  pinMode(53, OUTPUT);

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
    
  delay(100);

  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 

//delayMicroseconds(1);
  if (!SD.begin(5)) {
    Serial.println("initialization failed!");
  }


 //   digitalWrite(OLED_CS, LOW);
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
  // close the file:
    myFile.close();
    Serial.println("done. ");
    Serial.println("SDCard okay");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop()
{
  // nothing happens after setup
}
