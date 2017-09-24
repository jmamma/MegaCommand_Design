//MegaCommand Button & Encoder Test Firmware
//Version 1.0
//Author: Justin Mammarella & Manuel Odendahl
//Date: Sept 2017
//Description: Firmware to test the encoders and switches on the MegaCommand hardware
//             Run this firmware by uploading to the MegaCommand and then viewing the output of Serial Monitor at 9600bps
//             By rotating encoders and pressing each button you should see the corresponding bits change in the serial monitor output.
//Notes:       This firmware uses the Arduino Core.

#define SET_BIT(port, bit)   ((port) |= (1 << (bit)))
#define CLEAR_BIT(port, bit) ((port) &= ~(1 << (bit)))
#define TOGGLE_BIT(port, bit) ((port) ^= (1 << (bit)))
#define IS_BIT_SET(port, bit) (((port) & (1 << (bit))) ? 1 : 0)
#define IS_BIT_CLEAR(port, bit) (((port) & (1 << (bit))) == 0 ? 1 : 0)

/** 8-bit macros. **/
#define SET_BIT8(port, bit)   ((port) |= (uint8_t)(1 << (bit)))
#define CLEAR_BIT8(port, bit) ((port) &= (uint8_t)~(1 << (bit)))
#define IS_BIT_SET8(port, bit) (((port) & (uint8_t)(1 << (bit))) ? 1 : 0)
#define IS_BIT_CLEAR8(port, bit) (((port) & (uint8_t)(1 << (bit))) == 0 ? 1 : 0)

#define SR165_OUT    PL0
#define SR165_SHLOAD PL1
#define SR165_CLK    PL2

#define SR165_DATA_PORT PORTL
#define SR165_DDR_PORT  DDRL
#define SR165_PIN_PORT  PINL

#define SR165_DELAY() { } // asm("nop"); } // asm("nop");  asm("nop");  }

void my_clk() {
  CLEAR_BIT8(SR165_DATA_PORT, SR165_CLK);
  SET_BIT8(SR165_DATA_PORT, SR165_CLK);
}

void my_rst() {
  CLEAR_BIT8(SR165_DATA_PORT, SR165_SHLOAD);
  SET_BIT8(SR165_DATA_PORT, SR165_SHLOAD);

}

void my_init() {
 SR165_DDR_PORT |= _BV(SR165_SHLOAD) | _BV(SR165_CLK);
  //   digitalWrite(SR165_SHLOAD, LOW);
  
  CLEAR_BIT8(SR165_DDR_PORT, SR165_OUT);
  CLEAR_BIT8(SR165_DATA_PORT, SR165_OUT);
  SET_BIT8(SR165_DATA_PORT, SR165_CLK);
  SET_BIT8(SR165_DATA_PORT, SR165_SHLOAD);
}

uint16_t my_read16() {
  my_rst();

  uint16_t res = 0;
  uint8_t i = 0;
  for (i = 0; i < 16; i++) {
    res <<= 1;
    res |= IS_BIT_SET8(SR165_PIN_PORT, SR165_OUT);
    my_clk();
  }

  return res;
}

/**********************************************/

void setup() {
//  pinMode(SR165_OUT, INPUT);
 // pinMode(SR165_CLK, OUTPUT);
 // pinMode(SR165_SHLOAD, OUTPUT);
   Serial.begin(9600);

my_init();
  // put your setup code here, to run once:

}
 uint16_t oldsr = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
   uint16_t sr = my_read16();
   uint8_t count = 0;
   if (sr != oldsr) {

       for(uint8_t i=0; i< 16; i++)
    {
      
      Serial.print(sr >> i & 1, BIN);
      if (count < 8) {
      if (count % 2) { Serial.print(" "); }
      }
    
    else {
      Serial.print(" ");
    }
          count++;

    }
   
    Serial.print("\n");
   oldsr = sr;
}
   
}
