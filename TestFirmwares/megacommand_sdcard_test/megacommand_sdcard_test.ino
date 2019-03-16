//MegaCommand SDCard test
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test SDCard breakout board.
//             Run this firmware by uploading to the MegaCommand. The frmware will write a file called test.txt to the SDCard.
//             View the serial monitor at 9600bps to see the test results.
//
//             An array of size ARRAY_SIZE is filled with random bytes and is written to a file called test.txt y times. Where y = WRITE_ITERATIONS
//             The file is then read back and the stored data is checked against the array.
//Notes:       This firmware uses the Arduino Core.
//             The SDCard needs to be formatted to FAT32.


#include <SD.h>
#define RANDOM_SEED 123456789
#define ARRAY_SIZE 4096
#define WRITE_ITERATIONS 256
#define BYTES ARRAY_SIZE * WRITE_ITERATIONS

File myFile;
File myFile2;

void setup()
{
  // PL7: arduino pin 42, oled CS
  pinMode(42, OUTPUT);
  digitalWrite(42, HIGH);
  
  // PB0: arduino pin 53, SS
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);

  randomSeed(RANDOM_SEED);

  uint8_t my_array[ARRAY_SIZE];
  uint8_t random_number;
  int x, y;
  for (x = 0; x < ARRAY_SIZE; x++) {
    my_array[x] = (uint8_t) random(1, 255);
  }

  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  delay(100);

  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.

  //delayMicroseconds(1);

  bool ret = false;

  for (uint8_t n = 0; n < 5 && ret == false; n++) {
    ret = SD.begin(53);
    if (!ret) {
      Serial.print(".");
      delay(50);
    }
  }

  if(!ret)
  {
    Serial.println("initialization failed!");
  }

  Serial.println("initialization done.");
  SD.remove("test.txt");

  unsigned long count = 0;
  uint8_t myrandom = 0;
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    for (y = 0; y < WRITE_ITERATIONS; y++) {

      for (int x = 0; x < ARRAY_SIZE; x++) {
        count += myFile.write(my_array[x]);
      }
    }
    myFile.close();
    Serial.println("Wrote: ");
    Serial.print(count);
    Serial.println(" bytes");
    Serial.println("done. ");

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  uint8_t c;
  int8_t errors = 0;
  myFile = SD.open("test.txt", FILE_READ);
  if (myFile) {
    Serial.println("Reading contents from test.txt:");

    // read from the file until there's nothing else in it:
    for (y = 0; y < WRITE_ITERATIONS; y++) {

      for (int x = 0; x < ARRAY_SIZE; x++) {
        c = myFile.read();
        if (my_array[x] != c) {
          Serial.print(my_array[x]);
          Serial.print(" ");
          Serial.println(c);
          errors += 1;
          Serial.print("Data read did not match array");
        }
      }
    }
    if (errors > 0) {
      Serial.println("SDCard test failed. Data written does not match read");
    }
    else {
      Serial.println("SDCard read data matches RAM.");
    }
    Serial.println(" ");

    Serial.print("File Size: ");

    Serial.println(myFile.size());

    Serial.print("Wrote: ");
    Serial.println(count);

    // close the file:

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  if (myFile && myFile.size() !=  count) {
    Serial.println("SDCard test failed. Files size does not match bytes written");
  }
  else {
    Serial.println("SDCard test Success!. Files contents matches bytes written and size matches");
  }
  myFile.close();

}

void loop()
{
  // nothing happens after setup
}
