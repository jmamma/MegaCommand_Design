# MegaCommand

## Description:

The MegaCommand is an Arduino Mega compatible MIDI shield. 

4 Midi ports (2 in, 2 out)
4 Rotary Encoders + Push button
4 Buttons
1 LCD display
128KBytes of SRAM (0-63KB accessible natively, 64-128KB accessible with bank selection)
1 USB

## Project Status:

- Final PCBs 1_0_1 gerbers have been generated and are being fabricated for testing.

- Parts selection finalized.

- No guarantee that anything works until latest PCB design fully assembled on my end and tested.

- Sub systems (SD Card, MIDI, LCD, SRAM) have only been tested with the Arduino libraries, the MIDICtrl framework still needs a core written for the new hardware).


__ALL INFORMATION BELOW IS PROVIDED AS A CONVENIENCE AND COULD BE SUBJECT TO ERROR OR CHANGE.

## Parts:
[Bill of Materials](https://htmlpreview.github.io/?https://raw.githubusercontent.com/jmamma/MegaCommand_Design/master/megacommand_1_0_0c_bill_of_materials.htm)

[Mouser Cart (not a full list of materials)](http://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=189ae378fa)
Some of these components can be sourced cheaper than at mouser, so I would recommend doing your own shopping.
Also, the cart is incomplete, components such as LCD and SD Card breakout need to be purchased from Adafruit or alternative.


## Enclosure:

The enclosure is based on a standard 1590BB guitar pedal enclousre.

STL files for both the enclosure body and lid are provided in this git repository. The files can be 3D printed or you can investigate having an aluminium enclosure CNC milled.

## PCB Fabrication:
[PCBWay.com fabrication options](https://github.com/jmamma/MegaCommand_Design/blob/master/pcb_fabrication_preferences.jpg)

Gerber files (pcb layout diagrams used for fabrication) are included in the ./gerber/ directory above.

Download gerbers and submit to PCB manufacturer.

Circuit Schematic and Board Layout is present in Eagle files.

## About:

The MegaCommand shield was designed to be backwards compatible with the original MiniCommand hardware. 

However, there are notable differences between the two systems, including new pin assignments which must be taken account for when using the original MidiCtrl libraries.

The original MiniCommand used the ATMega64 microprocessor whilst the MegaCommand Shield is built on top of ArduinoMega which uses the ATMega2560 processor. The ATMega2560 shares most of the IO functionality of the ATMega64 but has many more additional pins, and a differernt pin-to-port layout.

The MegaCommand Shield accesses the ATMega2560 processor on board the ArduinoMega through the exposed jumpers, not all pins on the ATMega2560 are exposed through this Arduino interface.

Incorporating the differences between both processors and subsequent pin availability the following pin assignment has been made as the best possible substitutes for the original hardware layout.

## MegaCommand vs MiniCommand

4 Midi Ports vs 3
256k ROM vs 64K
USB vs No USB

--

MegaCommand pin changes from original MiniCommand are as followed:

MicroSD board:

CS = PB0

SRAM

BankSel = PL6

Key Scanning (Shift Registor Circuit):

PL0 = OUT
PL1 = SHIFT
PL2 = CLK

HD44780 LCD Circuit:

E = PL4
R/S = PL3

LEDs:

PE5 = LED0
PE4 = LED1

MIDI:

TXD0 and RXD0 (USART0) are reserved for Arduino USB interface.

Therefore we shift midi ports by 1.

MIDI Port 1:

RXD1 = MIDI Port 1 IN.
TXD1 = MIDI Port 1 OUT

Midi Port 2:

RXD2 = MIDI Port 2 IN
TXD2 = MIDI Port 2 OUT ( New port, not available on original Minicommand)





