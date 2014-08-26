## DC801 Event Badge for DC22 - Code

Brought to you by DC801, theTransistor, and 801 Labs

### Prerequisites

1. make
2. gcc-arm  https://launchpad.net/gcc-arm-embedded
  * Add gcc-arm bin folder to your system path


### Building your Binary

1. Edit code
2. run "make"


### Flashing New Code

1. Connect your smartbadge via usb, and set to programming mode
  * Put the badge in programming mode by holding down the second button, and hitting the reset button with a paper-clip, THEN releasing the second button.
2. run "make flash"
  * You may need to edit the end of "code/Makefile" to accommodate your preferences / distro.
  * Once you have a binary on the board, you can copy / paste it as you please in almost any operating system, though you may need to delete the old "firmware.bin" from the device first.


### Contributing to the codebase

1. Check out the todo.md ( Or come up with something new and awesome! )
2. Fix our stuff! ( Seriously, Thanks )
  * Please format your code (whitespacing, etc) before you submit!
  * Try to keep all code non-blocking. (Avoid delays / NOPs where possible.)
3. Document your changes
4. Submit your changes via Pull request on GitHub


### Questions

1. Twitter: @d3c4f
2. IRC: #dc801 on freenode
