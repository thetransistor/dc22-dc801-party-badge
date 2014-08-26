# Pin Mappings
This document is intended to be a quick reference to the pin mapping.

### BUTTONS
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| ~~14~~ | ~~PIO0_3~~ | ~~INPUT~~ | ~~BTN5 - internal pull-up (far left button)~~ |
| 13 | PIO1_20 | INPUT | BTN1 - internal pull-up |
| 4  | PIO0_1 | INPUT | BTN2 - internal pull-up / USB_FTOGGLE |
| 2  | PIO1_19 | INPUT | BTN3 - internal pull-up |
| 40 | PIO0_16 | INPUT | BTN4 / WAKEUP - externally pulled high |
| 3  | RESET | INPUT | externally pulled high (far right button) |

### BLUETOOTH
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 26 | PIO1_21 | OUTPUT | BLUE_NRESET |
| 27 | PIO0_8  | INPUT | MISO0 |
| 28 | PIO0_9 | OUTPUT | MOSI0 |
| 31 | PIO1_29 | OUTPUT | SCK0 |
| 30 | PIO0_22 | INPUT | BLUE_REQN |
| 45 | PIO0_17 | INPUT | BLUE_ACTIVE |

### VFD
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 15 | PIO0_4 | OUTPUT | VFD_PW_EN - active low, externally pulled high |
| 37 | PIO1_14 | OUTPUT | VFD_STB (strobe) |
| 38 | PIO1_22 | OUTPUT | MOSI1 |
| 43 | PIO1_15 | OUTPUT | SCK1 |

### USB
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 18 | PIO1_23 | INPUT | VBUS_SENSE |
| 22 | PIO0_6 | OUTPUT | USB_CONNECT (active low) |

### AUDIO
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 24 | PIO1_28 | OUTPUT | AUDIO OUT (use PWM?) |
| 25 | PIO1_31 | OUTPUT | AUDIO STANDBY - active low, externally pulled low |

### RGB LED
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 23 | PIO0_7 | OUTPUT | RGB_DATA |

### BATTERY STATUS
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 16 | PIO0_5 | INPUT | BAT_STAT2 - internal pull-up |
| 17 | PIO0_21 | INPUT | BAT_STAT1 - internal pull-up |

### DEBUGGING
| CHIP PIN | PORT_BIT | I/O | NOTES |
|----------|----------|-----|-------|
| 21 | PIO1_24 | OUTPUT | LED - for simple debugging |
| 46 | PIO0_18 | OUTPUT | RXD (3-pin header) |
| 47 | PIO0_19 | INPUT | TXD	(3-pin header) |
