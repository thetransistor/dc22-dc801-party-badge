// authored by: d3c4f

#include "buttons.h"
static void __attribute__ ((constructor)) Initialize(void);

static uint8_t buttonStates = 0b00000000;
static uint32_t buttonALast = 0;
static uint32_t buttonBLast = 0;
static uint32_t buttonCLast = 0;
static uint32_t buttonDLast = 0;

static uint32_t currentTicks = 0;


// Initialize the buttons
static void Initialize( void )
{
	// Set buttons as GPIO, Int PU Res, Hysteresis
	LPC_IOCON->PIO1_20	= (0 | 1<<4 | 1<<5);		// Button A
	LPC_IOCON->PIO0_1	= (0 | 1<<4 | 1<<5);		// Button B
	LPC_IOCON->PIO1_19	= (0 | 1<<4 | 1<<5);		// Button C
	LPC_IOCON->PIO0_16	= (0 | 1<<4 | 1<<5 | 1<<7);	// Button D

	// Set buttons as input
	LPC_GPIO->DIR[1] &= ~(1<<20);	// Button A
	LPC_GPIO->DIR[0] &= ~(1<<1);	// Button B
	LPC_GPIO->DIR[1] &= ~(1<<19);	// Button C
	LPC_GPIO->DIR[0] &= ~(1<<16);	// Button D, Also WAKEUP
									// Button E is RESET
}


// Update the Button States
static uint8_t UpdateButtonStates( void )
{
	buttonStates = 0b00000000; // Reset the current button states.
	// Update Button A
	if( LPC_GPIO->PIN[1] & (0x1<<20) ){
		buttonStates = buttonStates & 0b11111110;
	} else {
		buttonStates = buttonStates | 0b00000001; // A Pressed
	}

	// Update Button B
	if( LPC_GPIO->PIN[0] & (0x1<<1) ){
		buttonStates = buttonStates & 0b11111101;
	} else {
		buttonStates = buttonStates | 0b00000010; // B Pressed
	}

	// Update Button C
	if( LPC_GPIO->PIN[1] & (0x1<<19) ){
		buttonStates = buttonStates & 0b11111011;
	} else {
		buttonStates = buttonStates | 0b00000100;
	}

	// Update Button D
	if( LPC_GPIO->PIN[0] & (0x1<<16) ){
		buttonStates = buttonStates & 0b11110111;
	} else {
		buttonStates = buttonStates | 0b00001000;
	}

	return 0;
}


// Get the currentButtonStates
uint8_t GetButtonStates()
{
	UpdateButtonStates();
	return buttonStates;
}


// Check if a button has been pressed. *debounced
// TODO: Clean up this mess...
uint8_t ButtonPressed( eButton button )
{
	uint8_t currentButtonState = 0;
	uint32_t *currentButtonLast;
	currentTicks = getMsTicks();
	UpdateButtonStates();

	switch(button){
		case A:
			if( (buttonStates & 0b00001110) != 0) return 0; // Another button is also being pressed
			currentButtonState = buttonStates & 0b00000001;
			currentButtonLast = &buttonALast;
			break;
		case B:
			if( (buttonStates & 0b00001101) != 0) return 0; // Another button is also being pressed
			currentButtonState = buttonStates & 0b00000010;
			currentButtonLast = &buttonBLast;
			break;
		case C:
			if( (buttonStates & 0b00001011) != 0) return 0; // Another button is also being pressed
			currentButtonState = buttonStates & 0b00000100;
			currentButtonLast = &buttonCLast;
			break;
		case D:
			if( (buttonStates & 0b00000111) != 0) return 0; // Another button is also being pressed
			currentButtonState = buttonStates & 0b00001000;
			currentButtonLast = &buttonDLast;
			break;
		default:
			return 0;
			break;
	}

	if( currentButtonState == 0 ){
		// Button has been released. Reset for next press.
		*currentButtonLast = 0;
		return 0;
	} else {
		// Check if button is still being pressed
		if( *currentButtonLast > 1 ){
			if( currentTicks > *currentButtonLast + DEBOUNCE_PRESS_TIME ){
				*currentButtonLast = 1; // Don't report pressed again, until after released
				return 1;
			} else {
				return 0;
			}
		} else {
			if( *currentButtonLast == 0 ) *currentButtonLast = currentTicks;
			return 0;
		}
	}

	return 0;
}


// Check if more then one button has been pressed at the same time. *debounced
// TODO: Clean up this mess...
uint8_t ButtonsPressed( eButton button1, eButton button2 )
{

	// Check if only looking at a single button for some reason.
	if( button1 == button2 ) return ButtonPressed( button1 );

	uint8_t currentButton1State = 0;
	uint8_t currentButton2State = 0;
	uint32_t *currentButton1Last;
	uint32_t *currentButton2Last;

	currentTicks = getMsTicks();
	UpdateButtonStates();

	switch( button1 ){
		case A:
			currentButton1State = buttonStates & 0b00000001;
			currentButton1Last = &buttonALast;
			break;
		case B:
			currentButton1State = buttonStates & 0b00000010;
			currentButton1Last = &buttonBLast;
			break;
		case C:
			currentButton1State = buttonStates & 0b00000100;
			currentButton1Last = &buttonCLast;
			break;
		case D:
			currentButton1State = buttonStates & 0b00001000;
			currentButton1Last = &buttonDLast;
			break;
		default:
			return 0;
			break;
	}

	switch( button2 ){
		case A:
			currentButton2State = buttonStates & 0b00000001;
			currentButton2Last = &buttonALast;
			break;
		case B:
			currentButton2State = buttonStates & 0b00000010;
			currentButton2Last = &buttonBLast;
			break;
		case C:
			currentButton2State = buttonStates & 0b00000100;
			currentButton2Last = &buttonCLast;
			break;
		case D:
			currentButton2State = buttonStates & 0b00001000;
			currentButton2Last = &buttonDLast;
			break;
		default:
			return 0;
			break;
	}

	// Check if either button is released. Reset timer as needed.
	if( currentButton1State == 0 ) *currentButton1Last = 0;
	if( currentButton2State == 0 ) *currentButton2Last = 0;

	// Check if both buttons are pressed.
	if( currentButton1State != 0 && currentButton2State != 0 ){

		if( *currentButton1Last > 1 && *currentButton2Last > 1 ){
			if( (currentTicks > *currentButton1Last + DEBOUNCE_PRESS_TIME_2) && (currentTicks > *currentButton2Last + DEBOUNCE_PRESS_TIME_2) ){
				*currentButton1Last = 1; // Don't report pressed again, until after released
				*currentButton2Last = 1; // Don't report pressed again, until after released
				return 1;
			} else {
				return 0;
			}
		} else {
			if( *currentButton1Last == 0 ) *currentButton1Last = currentTicks;
			if( *currentButton2Last == 0 ) *currentButton2Last = currentTicks;
			return 0;
		}

	} else {
		return 0;
	}

	// Should never get here.
	return 0;
}
