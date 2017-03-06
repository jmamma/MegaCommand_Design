The MegaCommand shield was designed to be backwards compatible with the original MiniCommand hardware. 

There are however notable differences between the two, including new pin assignments which must be taken account for when using the original MidiCtrl libraries.

The original MiniCommand used the ATMega64 microprocessor whilst the MegaCommand Shield is built on top of the ATMega2560. The ATMega2560 shares a mostly identical pin layout to the ATMega64 but has many more additional pins. 

The MegaCommand Shield accesses the ATMega2560 processor on board the ArduinoMega through the exposed jumpers, not all pins on the ATMega2560 are exposed through this Arduino interface.


MegaCommand pin changes from original MiniCommand are as followed:

MicroSD board -

CS pin is now PL6

Key Scanning: Shift Registor Circuit

PL0 = OUT
PL1 = SHIFT
PL2 = CLK

HD44780 LCD Circuit -

E = PL4
R/S = PL3

LEDs -

PE5 = LED0
PE4 = LED1

MIDI -

TXD0 and RXD0 (USART0) are reserved for Arduino USB interface.

Therefore we shift midi ports by 1.

MIDI Port 1:

RXD1 = MIDI Port 1 IN.
TXD1 = MIDI Port 1 OUT

Midi Port 2:

RXD2 = MIDI Port 2 IN
TXD2 = MIDI Port 2 OUT ( New port, not available on original Minicommand)





