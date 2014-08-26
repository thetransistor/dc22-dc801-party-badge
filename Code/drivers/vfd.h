// authored by: d3c4f

#ifndef __VFD_H
#define __VFD_H

#ifdef __cplusplus
	extern "C" {
#endif

// INCLUDES
#include "core/inc/lpc13uxx_gpio.h"
#include "drivers/ssp1.h"

// STROBE AND CLOCK MACROS
#define VFD_STROBE_START { uint8_t i; LPC_GPIO->CLR[ 1 ] = (1 << 14); for( i=0; i<48; i++ ) __NOP(); }
#define VFD_STROBE_STOP { uint8_t i; LPC_GPIO->SET[ 1 ] = (1 << 14); for( i=0; i<48; i++ ) __NOP(); }
#define VFD_START_BYTE		0b11111010
#define VFD_COMMAND_BYTE	0b11111000
#define VFD_BUFFER_LENGTH	40
#define VFD_BUFFER_HEIGHT	2

typedef enum {
	NOTINITIALIZED,
	INITIALIZING,
	INITIALIZED,
	POWEREDOFF,
	BUSY
} eVFDStatus;

typedef enum {
	VFD_ON,			// turn on 40v power the VFD
	VFD_OFF,		// turn off 40v power to the VFD
	VFD_INIT,		// turn on VFD, no blink, no cursor
	VFD_INIT2,		// turn on VFD, blink, cursor
	VFD_CLEAR,		// clear the VFD and return to "home" position (0,0)
	VFD_HOME		// returns the cursor to the "home" position (0,0)
} eVFDCommand;


uint8_t VFDInit( void );
eVFDStatus VFDGetStatus( void );
uint8_t VFDGetPositionX( void );
uint8_t VFDSendCommand( eVFDCommand );
uint8_t VFDSetBrightness( uint8_t );
uint8_t VFDGetBrightness( void );
uint8_t VFDSetPosition( uint8_t, uint8_t );
uint8_t VFDWriteChar( char );
uint8_t VFDWriteChar2( uint8_t, uint8_t, char newChar );
void VFDWriteText( char*, uint8_t, uint8_t, uint8_t );
// Additional functions for text in the vfdtext library

#ifdef __cplusplus
}
#endif

#endif
