# DC801 Event Badge for DC22
Brought to you by DC801, theTransistor, and 801 Labs


## Extra special thanks to the few key people in this project.
+ **devino**, for the hardware design, and PCB population
+ **nemus**, for code / sanity
+ **yukaia**, for the bulk of the assembly / sanity
+ **Isaac / RustedFriend**, for machining the HPDE
+ **DC801**, for "hacking all the things" ;)


### Notes
There has been some confusion on the charging circuit. First, NO the battery should not burst into flames and kill everything if you leave it plugged in, charging. The batter has a built-in over / under voltage / thermal protection circuit.

The battery charging chip also has some protection circuits built-in. To be safe, don't leave the battery in the sun / anywhere too hot / cold. And try not to physically abuse it.

If you run your battery "empty", it might have a problem charging, as it will try to power the VFD on, which takes about 200mA initially. You currently have 2 easy options (we will fix this in firmware).
1. Put the badge in programming mode by holding down the second button, and hitting the reset button with a paper-clip.
2. Use a 1amp+ dedicated USB charger instead of a computer port to charge the battery.


## Status
Despite coming with a basic firmware, your DC801 party badge has some very nice hardware features that can be enabled by flashing future firmware to the device. Please subscribe to the repository for future updates.


## Capabilities of the badge
**Chipset / Hardware:**

1. NXP LCP1347 mCU - Changed from the STM32 chip that was originally planned.
  * 72 MHZ Arm mCU
  * 32 bit instruction set
  * 64 kB flash
  * 8  kB ram
  * 4  kB EEPROM
2. nRF8001 Bluetooth LE module
3. MCP73833-FCI/UN LiPo Charger
  * Low Voltage Protection
4. CU16025-UW6J 16x2 VFD Display
5. IS31AP4991 AB Audio Amplifier w/ mini speaker
6. WS2812B RGB Led
7. Test LED (on the rear of the board)
8. 4 User Buttons, and 1 Reset Button
9. "2000" mAH Battery
10. Staying on your wrist. Because neck-badgers are for n00bs.  

**Things you *should* do with this badge (with additional programming)**

1. Connect to your laptop or smartphone (via bluetooth modules)
2. Use it as a watch; The BTLE should be able to function as an RTC
3. RBG LED Status LED
4. Buttons, Buttons, Buttons! (Well, like 4 of them.)
5. Square, Wave audio. We've included a good sized speaker and an audio amp. Unce unce unce!
6. Hack it. Extra GPIO up top should allow your creative juices to flow. (gross)

## Flashing new firmware to your badge
No special cables or software is required to flash pre-built images! :D

1. Connect the device to your computer. (linux, mac, osx, etc)
2. Hold down the second button (bootloader) from the left, and press the reset button (use a paper-clip, etc)
  * Continue to hold down the (bootloader) button while you release the reset button.
  * The device should now present itself as a Mass Storage Device
3. Delete the firmware.bin file that is currently on the device.
4. Copy your new firmware image to the device.
5. Press and release the reset button once the file has finished copying.
6. ???
7. Profit.

## Updates
New firmware should be released on the github, along with the source code. If you have a feature request, please contact us through github. Code updates should continue for the next several months or longer.

## Schematic / Board Notes
We have applied a couple of hotfixes to v0.1 of the pcb, including:

1. Removing the first button from the board and rerouting the to the USB
2. Removing the Resistor that was connecting the BTLE RDYN to the P0_16
3. Rerouting the BTLE RDYN to the VFD Strobe
