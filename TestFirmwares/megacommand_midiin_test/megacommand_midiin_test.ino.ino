//MegaCommand MIDI-in test firmare.
//Version 1.0
//Author: Justin Mammarella. Based on Staffan Melin's MIDI Arduino tutorial. http://libremsicproduction.com/
//Date: Sept 2017
//Description: Firmware to test the MIDI input ports on the MegaCommand Hardware
//             Run this firmware by uploading to the MegaCommand and then sending MIDI note data to MIDI input ports 1 & 2.
//             You should see the note messages detected as indicated by the Serial Monitor output. 
//Notes:       This firmware uses the Arduino Core. Serial monitor conected at 9600bps

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(31250);
  Serial2.begin(31250);

  Serial.begin(9600);
  Serial.println("MegaCommand MIDI In Test Firmware");
}
#define MIDI_NOTE_ON 144
#define MIDI_NOTE_OFF 128

const int filterChannel = 0; // MIDI channel 1
const int filterNote = 60; // middle C

// states
#define STATE_NONE 0
#define STATE_NOTE_ON 1
#define STATE_NOTE 2
#define STATE_NOTE_OFF 3

int state = 0;

// keep action (LED) going for actionDuration milliseconds
bool actionOn;
unsigned long actionTime;
unsigned long actionDuration = 100;

// received MIDI data
uint8_t serial_read;
byte channel;
byte cmd_byte;
byte midiNote;
byte midiVelocity;

void playNote(byte note, byte velocity) {
  Serial.print(note);
  Serial.println("a");
}
void printBits(byte myByte) {
  for (byte mask = 0x80; mask; mask >>= 1) {
    if (mask  & myByte)
      Serial.print('1');
    else
      Serial.print('0');
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);

}


void loop() {

  if (Serial1.available() > 0) {

    serial_read = Serial1.read();


    switch (state) {

      case STATE_NONE:

        // remove channel info
        channel = serial_read & 0x0F;
        cmd_byte = serial_read & 0xF0;

        if (cmd_byte == MIDI_NOTE_ON)
        {

          state = STATE_NOTE_ON;
        }
        if (cmd_byte == MIDI_NOTE_OFF) {
          state = STATE_NOTE_OFF;
          
        }

        //  }
        break;
    case STATE_NOTE_ON:
              Serial.println("note on port 1");

        midiNote = serial_read;
        Serial.println(midiNote, HEX);
        state = STATE_NOTE;

        break;
    case STATE_NOTE_OFF:
              Serial.println("note off port 1");

        midiNote = serial_read;
        Serial.println(midiNote, HEX);
        state = STATE_NOTE;

        break;


      case STATE_NOTE:
        midiVelocity = serial_read;
        state = STATE_NONE;
        

        if (midiNote == filterNote && midiVelocity > 0)
        {
          actionTime = millis();
          actionOn = true;
        }

        break;

    } // switch

  }
   if (Serial2.available() > 0) {

    serial_read = Serial2.read();


    switch (state) {

      case STATE_NONE:

        // remove channel info
        channel = serial_read & 0x0F;
        cmd_byte = serial_read & 0xF0;

        if (cmd_byte == MIDI_NOTE_ON)
        {

          state = STATE_NOTE_ON;
        }
        if (cmd_byte == MIDI_NOTE_OFF) {
          state = STATE_NOTE_OFF;
          
        }

        //  }
        break;
    case STATE_NOTE_ON:
              Serial.println("note on port 2");

        midiNote = serial_read;
        Serial.println(midiNote, HEX);
        state = STATE_NOTE;

        break;
    case STATE_NOTE_OFF:
              Serial.println("note off port 2");

        midiNote = serial_read;
        Serial.println(midiNote, HEX);
        state = STATE_NOTE;

        break;


      case STATE_NOTE:
        midiVelocity = serial_read;
        state = STATE_NONE;
        

        if (midiNote == filterNote && midiVelocity > 0)
        {
          actionTime = millis();
          actionOn = true;
        }

        break;

    } // switch

  }

}



