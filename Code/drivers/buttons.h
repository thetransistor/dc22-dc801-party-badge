// authored by: d3c4f

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "main.h"

#define DEBOUNCE_PRESS_TIME      40 // debounce ms for single-button
#define DEBOUNCE_PRESS_TIME_2   100 // debounce ms for multi-button

typedef enum {
    A,
    B,
    C,
    D
} eButton;

uint8_t GetButtonStates( void );
uint8_t ButtonPressed( eButton );  // *Debounced
uint8_t ButtonsPressed( eButton, eButton ); // *2 Buttons simult. pressed

#endif
