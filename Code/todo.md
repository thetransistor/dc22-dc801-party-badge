##TODO

###libraries/vfdtext
- finish
- Expand animations

###drivers/ssp1

- modify ssp1Send() and sspSend() to be non-blocking
- implement a buffer either here, or in the drivers/vfd
- change output to 16 bit

###drivers/vfd

- modify strobing to be non-blocking
- modify send functions to be non-blocking
- perhaps implement a frameBuffer, and scan? (ignoring on-chip display buffer)
  - also consider implementing a command buffer
- add "string" handling
- change to work with 16 bit instruction / data pairs


###drivers/ws2812b

- bitbang the values for 1 wire(grb?).


###other todo

1. Clean up formatting
2. Speaker / Tone Library using timer interupts
3. Power Control for the mCU (low power / sleep modes)
4. EEPROM implementation for Read / Write backup data
5. User Interface Menus / Display
6. Merge debug mode in with a 2nd stage bootloader
7. BTLE Library, review hardware setup
8. RTC through BTLE chip (has separate crystal for BTLE / BTLE RTC)
9. Implement proper Null-Terminated strings, or Linked-List String-Objects
