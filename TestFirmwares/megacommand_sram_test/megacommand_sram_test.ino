//MegaCommand SRAM Test Firmware
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test the external SRAM by copying randomized data between banks then comparing reads.
//             Run this firmware by uploading to the MegaCommand and then viewing the output of Serial Monitor at 9600bps
//             The test will take about 5 minutes to run.
//Notes:       This firmware uses the Arduino Core.

#define BANK_SELECT 43
#define RANDOM_SEED 123456789


void select_bank(uint8_t bank) {
     if (bank == 0) {
     digitalWrite(BANK_SELECT, LOW);    }
    if (bank == 1) {
     digitalWrite(BANK_SELECT, HIGH); 
    }
}

void setup() {
  randomSeed(RANDOM_SEED);
  
  Serial.begin(9600);
  Serial.println("MegaCommand SRAM Test");

  XMCRA = _BV(SRE); //ENABLE MEM
  
  pinMode(43, OUTPUT);
  select_bank(0);
    char hex[4];

  volatile uint8_t *ptr;      
  uint8_t myrandom = 0;
  uint8_t random_number, read_bank0, read_bank1;
  for (ptr = reinterpret_cast<uint8_t *> (0x2200); ptr <= reinterpret_cast<uint8_t *> (0xFFFF); ptr++) {
    sprintf(hex, "%04X", ptr);

//  Serial.println("\nTesting Address ");
  Serial.println(hex);

    select_bank(0);
    //Generate random number, store in stack
    random_number = random(1,255);
    //Copy random number to bank0 mem location
    *ptr = random_number;
    //Read back the random number
    read_bank0 = *ptr;

    select_bank(1);

    //Write the read from bank0 in to bank1
    *ptr = read_bank0;
    //Read back bank1 write
    read_bank1 = *ptr;
       //     Serial.println(random_number);

       // Serial.println(read_bank0);
       // Serial.println(read_bank1);
    if ((read_bank0 == 0) || (read_bank1 == 0))  {
        Serial.println("\nFailed bank0 zero reading");
     Serial.println(hex);
     return;
    }
    if (read_bank0 != random_number) {
     Serial.println("\nSRAM Test Failed bank0 mismatch ");
     Serial.println(hex);
     return;

    }
    if (read_bank1 != random_number) {
     Serial.println("\nSRAM Test Failed bank1 mismatch");
     Serial.println(hex);

    return;
    }
  }

  Serial.println("Congratulations. SRAM Test: Passed");

}

void loop() {
  // put your main code here, to run repeatedly:


}
