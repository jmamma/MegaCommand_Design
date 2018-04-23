# MegaCommand

## Description:

The MegaCommand is an Arduino Mega MIDI shield that is backwards compatible with the R&W MiniCommand hardware and MIDICtrl framework. The PCB is a through-hole design (no SMD soldering skills required). 

* 4 x Midi ports (2 in, 2 out)
* 4 x Rotary Encoders + Push button
* 4 x Buttons
* 1 x LCD display (Choose between OLED or LCD)
* 128KBytes of SRAM (0-63KB accessible natively, 64-128KB accessible with bank selection)
* 1 x Dual Channel 12bit DAC
* 1 x USB

## Project Status:

- Final PCBs 1_0_1a gerbers have been tested and built

- Parts selection finalized.

- Sub systems (SD Card, MIDI, LCD, SRAM) have been tested with the Arduino libraries and MIDICtrl framework.

- An arduino core for the ArduinoMega has been written and tested. MidiCtrl 20 has been modified to run on the ArduinoMega and compile in the Arduino IDE. The MCLive firmware is running successfully on the MegaCommand. 

- Compile errors for Wesen's firmwares. Only MCLive firmware compiles at this time.


__ALL INFORMATION BELOW IS PROVIDED AS A CONVENIENCE AND COULD BE SUBJECT TO ERROR OR CHANGE.

## Parts:
[Bill of Materials](https://docs.google.com/spreadsheets/d/1SPOctEUJUs_R-fi7xMjIrdiOk7FmjT5jRd9NrTtHMDI/edit?usp=sharing)

[Mouser Cart (not a full list of materials)](
http://au.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=bd455aeb97)
Some of these components can be sourced cheaper than at mouser, so I would recommend doing your own shopping.
Also, the cart is incomplete, components such as LCD and SD Card breakout need to be purchased from Adafruit or alternative.

## Display

The MegaCommand board has support for 2 display types.

Only the HD44780 display is working with the MIDICtrl library and MCLive firmware at this stage.
Porting the display libraries over to OLED is planned for a later release. Users can choose to upgrade to the OLED the display at a later stage.

1) HD44870 LCD is the original LCD used in the MiniCommand and compatible with the LCD libraries.
2) OLED 128x32 display is a new display of similar size but with fully customizable display capable of 4 lines of text and custom  graphics, it uses the SPI bus. (OLED display requires resistor position changes to enable SPI mode as per adafruit documentation https://learn.adafruit.com/2-3-monochrome-128x32-oled-display-module/assembly-1):

## Build 

Videos detailing the build process (annotations to follow).

MegaCommand 1.0.1a:
https://www.youtube.com/watch?v=15qRWJqVOe8

Optional OLED display install:
https://www.youtube.com/watch?v=Sr32vFOjeSc

```
VERIFY CHIP ORIENTATION BEFORE SOLDERING.

Take care in making sure the ICs are inserted the correct way around.

You do not want to have to try and desolder 32 pins.

https://github.com/jmamma/MegaCommand_Design/blob/master/megacommand_1_0_1a_top_diagram.pdf
https://github.com/jmamma/MegaCommand_Design/blob/master/megacommand_1_0_1a_bottom_diagram.pdf

## Build Order: 

  1. ICS: RAM, Octal Latch, Shift Registers
  2. Arduino male headers. 
  3. Capacitors. (Make sure the 220uF electrolytic cap fits when the arduino is connected)

TEST POINT: Run the SRAM firmware test.

  4. MEC switches (Make sure these sit completely flush with the board and are not leaning to one side)
  5. LCD Trimmer
  6. Resistor arrays
  7. Encoders (Make sure these sit completely flush with the board and are not leaning to one side)  
  
TEST POINT: Run the button and encoder test firmware.
  8. ICS: MIDI Optocouplers, HEX buffer, DAC 
  9. Resistors + diodes
10. MIDI DIN ports. (completly remove the 2 front pins by pulling the entire piece of aluminum from the connector)
 
TEST POINT: Run the MIDIPort test firmware.

 11. Power Jack (+9V tip)
 12. SDCard headers (the female header is placed on the bottom side of the board, and the pins are soldered from the top side. Solder male headers to the sd-card breakout board)
 
TEST POINT: Run the SDCARD test firmware
 
 13. Display header HD44780 (soldered from the top side of the board, the bottom side is intentionally obstructed by MIDI ports). There are 2 display header locations, one for each display type, choose the correct one.
 14. Display HD44780 (Soldered to the display header once the header is installed, max height of display should be 1.5-2mm above mec switches (without switch cap).
 15. LEDs (+ anode pin nearest to the bottom of the board for both LEDs. )
 16. Power switch. (optional, you can solder a short between the two right most pins on EG1212B  
 
TEST POINT: Run the LCD and LED test firmware.

## Important

The MIDI DIN ports and display should be installed last.

The MIDI DIN ports get soldered on before the display, and require that the 2 front legs are removed from each DIN connector (don't just cut the legs, pull the entire piece of aluminium out with a pair of pliers, this will prevent shorts with the display header). Once the MiDI DIN ports are in. The header for the HD44780 display is soldered from the display side of the board; the reverse side in which you would normally solder from is intentionally obstructed by the MIDI ports.

This is not ideal, but was necessary due to the space limitations of the board.

Display height. the top of the display (OLED or HD44780) should sit no higher than 1.5-2mm above the the height of the switches (without switch cap). This should allow the display and buttons to sit nicely if you use the enclosure design.

5) To install the male headers that connect to the MC to the ArduinoMega, insert the headers in to the ArduinoMega then solder with the arduino attached to the headers. This will ensure perfect alignment. See the youtube video.
```

## Enclosure:

The enclosure is based on a standard 1590BB guitar pedal enclousre.

STL files for both the enclosure body and lid are provided in this git repository. The files can be 3D printed or you can investigate having an aluminium enclosure CNC milled.

Currently the body enclosure has an LCD cut out for the HD44780 display. A new design will need to be generated for the OLED.

## PCB Fabrication:
[PCBWay.com fabrication options](https://github.com/jmamma/MegaCommand_Design/blob/master/pcb_fabrication_preferences.jpg)

Gerber files (pcb layout diagrams used for fabrication) are included in the ./gerber/ directory above.

Download gerbers and submit to PCB manufacturer.

Circuit Schematic and Board Layout is present in Eagle files.

## About:

The MegaCommand shield was designed to be backwards compatible with the original MiniCommand hardware. 

However, there are notable differences between the two systems, including new pin assignments which must be taken account for when using the original MidiCtrl libraries.

The original MiniCommand used the ATMega64 microprocessor whilst the MegaCommand Shield is built on top of ArduinoMega which uses the ATMega2560 processor. The ATMega2560 shares most of the IO functionality of the ATMega64 but has additional pins, and a differernt pin-to-port layout.

The MegaCommand Shield accesses the ATMega2560 processor on board the ArduinoMega through the exposed headers, not all pins on the ATMega2560 are exposed through this Arduino interface.

Incorporating the differences between both processors and subsequent pin availability the following pin assignment has been made as the best possible substitutes for the original hardware layout.

## Arduino IDE, Cores & MIDICtrl library

Once you've built a MegaCommand you can write sketches within the Arduino IDE to test the hardware and run custom firmwware.
Before you start coding you need to decide which core you are going to use.

## Arduino Cores
In ArduinoLand, a Core is a collection of initialisation functions and associated libraries, used for configuring the underlying hardware; it is analogous to an Operating System kernel.

There are two cores to keep in mind:

Arduino Core:

This is the standard core, that comes installed default with the Arduino IDE. If you use this core with the MegaCommand you can program the MegaCommand like an ordinary arduino shield. The built in arduino functions can be used to control the hardware using the pin assignement detailed below.

MegaCommand Core:

This is based on Wesen's core for the MiniCommand and allows the MIDICtrl framework to run on the ArduinoMega.
By using this core you can take advantage of the powerful MIDI libraries and GUI functionality.

For example, the MegaCommand core is necessary for running the MCL firmware and controlling the Elektron instrument range.


### Installing the MIDICtrl core.
(Instructions for OSX, should be similar for Windows)

1) Download the Arduino IDE https://www.arduino.cc/en/Main/Software (1.8.5 tested)

2) Get the MIDICtrl library and MegaCommand Core (same repo):
```
   cd /Applications/Arduino.app/Contents/Java/hardware/
   git clone https://github.com/jmamma/MIDICtrl20_MegaCommand
```
### Selecting the Core

1) Open the Arduino IDE, Under the Tools menu, select the core you wish to use from the "Board:" menu

The default Arduino core is named "Arduion/Genuino Mega or Mega 2560"

The MegaCommand core will be listed at the bottom. 

## MegaCommand vs MiniCommand
```
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
```




