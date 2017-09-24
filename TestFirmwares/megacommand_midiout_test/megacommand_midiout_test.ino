//MegaCommand MIDI-out test firmare.
//Version 1.0
//Author: Justin Mammarella
//Date: Sept 2017
//Description: Firmware to test the MIDI Output ports on the MegaCommand Hardware
//             Run this firmware by uploading to the MegaCommand and then viewing the output of the MIDI ports, using
//             a midi interface. You should see MIDI note on and note off messages on both ports.
//Notes:       This firmware uses the Arduino Core.

void setup() {
  //  Set MIDI baud rate:
    Serial1.begin(31250);
    Serial2.begin(31250);
}

void loop() {
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note off (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
  Serial2.write(cmd);
  Serial2.write(pitch);
  Serial2.write(velocity);
}
