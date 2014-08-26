// authored by: d3c4f

#include "vfd.h"
#include <string.h>

// Status of the VFD (property)
static eVFDStatus VFDStatus = NOTINITIALIZED;

static uint8_t currentPositionX = 0;
static uint8_t currentPositionY = 0;
static uint8_t currentBrightness = 255;

// Initialize the VFD, set pin directions, etc.
uint8_t VFDInit()
{
	if ( VFDStatus == NOTINITIALIZED ){
		LPC_GPIO->DIR[PORT0] |= (1<<4);		// VFD Power
		LPC_GPIO->DIR[PORT1] |= (1<<14);	// VFD Strobe
		LPC_GPIO->DIR[PORT1] |= (1<<15);	// VFD Clock
		LPC_GPIO->DIR[PORT1] |= (1<<22);	// VFD Data
		ssp1Init(); // Initialize SPI for the VFD
	}

	// Turn on the 40v VFD Power, and Initialize the VFD
	if(VFDSendCommand(VFD_ON) != 0){
		return 1;
	}

	VFDStatus = INITIALIZED;
	return 0;
}


// Returns the current VFD status
eVFDStatus VFDGetStatus()
{
	return VFDStatus;
}


// Returns the current X position
uint8_t VFDGetPositionX()
{
	return currentPositionX;
}


// Returns the current brightness
uint8_t VFDGetBrightness()
{
	return currentBrightness;
}


// Send a command code to the VFD
uint8_t VFDSendCommand( eVFDCommand command )
{

	if ( command == VFD_OFF ){
		// Turn off the VFD
		LPC_GPIO->SET[PORT0] = 1<<4;	// Turn off the VFD Power
		VFDStatus = POWEREDOFF;
		return 0;

	} else if ( command == VFD_ON ) {
		// Turn on the VFD and Initialize it
		VFDStatus = NOTINITIALIZED;

		VFD_STROBE_STOP; // Initialize the Strobe line
		LPC_GPIO->CLR[PORT0] = 1<<4; // Turn on the 40v VFD Power

		// Initialize the VFD driver
		if( VFDSendCommand(VFD_INIT) == 0 ){
			// Set position to 0,0 and use Euro font set
			if( VFDSendCommand(VFD_HOME) == 0 ){
				VFDStatus = INITIALIZED;
				return 0;
			} else {
				return 1;
			}
		} else {
			return 1;
		}
		return 1; // Should never reach this point

	} else {
		// Commands requiring VFD SPI Data
		if (VFDStatus == POWEREDOFF) return 1; // VFD is not powered on
		if (VFDStatus != INITIALIZED && command != VFD_INIT && command != VFD_INIT2) return 1;

		VFD_STROBE_START;
		sspSend(VFD_COMMAND_BYTE);

		switch( command ){
			case VFD_CLEAR:
				sspSend(0b00000001);	// Clear VFD and return to "home" position (0,0)
				currentPositionX = 0;
				currentPositionY = 0;
				break;
			case VFD_INIT:
				sspSend(0b00001100);	// Turn on display, turn off cursor, turn off blink.
				VFDStatus = INITIALIZED;
				currentBrightness = 255;
				break;
			case VFD_INIT2:
				sspSend(0b00001111);	// Turn on display, turn on cursor, turn on blink.
				VFDStatus = INITIALIZED;
				currentBrightness = 255;
				break;
			case VFD_HOME:
				sspSend(0b00000011);	// Returns the cursor to the "home" position (0,0), and set Japanese fontset(last bit)
				currentPositionX = 0;
				currentPositionY = 0;
				break;
			default:
				break;
		}

		VFD_STROBE_STOP;
		return 0;

	}

	// How the hell did we get here???
	return 1;
}


// Set the VFD brightness
uint8_t VFDSetBrightness( uint8_t newBright )
{
	if (VFDStatus != INITIALIZED) return 1; // VFD is not initialized
	currentBrightness = newBright;

	newBright = ~newBright;
	newBright >>= 4;
	newBright &= 0b00001111;
	newBright |= 0b00110000;

	VFD_STROBE_START;
	sspSend(VFD_COMMAND_BYTE);
	sspSend(newBright);
	VFD_STROBE_STOP;

	return 0;
}


// Set the current cursor position
uint8_t VFDSetPosition( uint8_t y, uint8_t x )
{
	if (VFDStatus != INITIALIZED) return 1; // VFD is not initialized
	if( x >= VFD_BUFFER_LENGTH || y >= VFD_BUFFER_HEIGHT ) return 1; // Out of bounds

	uint8_t newPosition = 0b10000000;
	if( y == 1 ) newPosition |= 0b01000000;
	newPosition |= x;

	VFD_STROBE_START;
	sspSend(VFD_COMMAND_BYTE);
	sspSend(newPosition);
	VFD_STROBE_STOP;

	currentPositionX = x + 1;
	currentPositionY = y;

	return 0;
}


// Write a character to the VFD at the current position
uint8_t VFDWriteChar( char newChar )
{
	if( VFDStatus != INITIALIZED ) return 1; // VFD is not initialized
	if( currentPositionX >= VFD_BUFFER_LENGTH ) return 1; // Out of bounds

	VFD_STROBE_START;
	sspSend(VFD_START_BYTE);
	sspSend(newChar);
	VFD_STROBE_STOP;

	currentPositionX += 1;

	return 0;
}


// Write a character to the VFD at a specific location
uint8_t VFDWriteChar2( uint8_t y, uint8_t x, char newChar )
{
	if( VFDSetPosition( y, x ) == 0 )
	{
		if( VFDWriteChar( newChar ) == 0 ){
			return 0;
		} else {
			return 1;
		}
	} else {
		return 1;
	}

	return 1; // Impossible.
}


// Place an array of characters onto the VFD at a specific location
void VFDWriteText( char* text, uint8_t length, uint8_t y, uint8_t x){
	uint8_t position = 0;

	// Set the current position
	if( VFDSetPosition( y, x ) != 0 ) return;

	// Place each character
	while( position < length ){
		VFDWriteChar( text[position] );
		position += 1;
	}
}
