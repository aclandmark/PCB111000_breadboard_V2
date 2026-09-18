# PCB111000_breadboard_V2


Introducing C for the microcontroller


PCB111000_UNO_V2 has a bespoke bootloader that runs on the Atmega 328 (UNO) device.

An edited version of this bootloader is used with PCB111000_breadboard_V2 and runs on an Atmega 168.

All non essential features such as the text programmer have been removed.
The resulting code is divided between the following 3 projects.

Hex verification:  This sits near the bottom of the application partition

Bootloader launcher: This sets the hardware and sits at the bottom of the application partition

The bootloader:    This sits in the bootloader partition

User programs can occupy the space between 0x000 and 0x3000 i.e. 75% of the 16kB memory

This Atmega 168 can now be plugged into breadboard along with a USB bridge (CP2102 module)
and one or two four digit 7 segment dispays. This hardware is basic and cheep enough 
to be assembled by students at home and a number of sample projects are presented for this 
component set up. A display can easily be removed and other components such as leds, piezzo sounder, 
analogue voltage source etc can be added enabling more varied projects to be developed.


The development environment is provided by Arduino used together with the Br@y++ terrminal program.
The bootloader is slightly different from the one provided by Arduino.  The host device does not 
require an external resonator but runs off its internal RC clock. A watch crystal is placed accross 
the crystal ports.  This is used to calibrate the internal RC clock.  
It also enables simple code for a 24 hour clock to be written.


