# Board-Test : Pre-Compiled Binarie(s) for your convenience

This directory should contain binarie(s) for testing the basic features of your smartbadge.

## Current Tests Included

1. VFD : Power On / Off, Display Characters, Change Brightness
2. Buttons A, B, C, D : States, Debouncing, Multi-Button
3. Debug LED on rear of board (hard to see while in case)
4. Power State : "Charging", "On-Battery" states

## Future Tests Include
1. RGB Status LED
2. mCU Power States
3. Audio / Speaker Checks
4. EEPROM Read / Write
5. RTC Tests
6. Bluetooth Tests

## Using the Board-Test binaries

1. Upon powering up, the display should initialize with the following"
  * VFD at 100% Brightness
  * VFD Top-Row animation
  * A, B, C, D button state checks in the lower-left of the VFD
  * Power-State in the Lower-Right :
    * (C) Charging
    * (D) Done Charging (won't ever reach this state at full brightness)
    * (B) On Battery (or no-USB power)
2. Pressing Button A will increase the brightness
3. Pressing Button B will decrease the brightness
4. Pressing Buttons A and B simultaneously will turn OFF the VFD
5. Pressing Buttons C and D simultaneously will turn ON the VFD
