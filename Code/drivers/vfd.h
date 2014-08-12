/**
 * @brief Defines for the VFD interface
 * @file vfd.h
 */

#ifndef __VFD
#define __VFD

#ifdef __cplusplus
	extern "C" {
#endif

// INCLUDES
#include "core/inc/lpc13uxx_gpio.h"
#include "drivers/ssp1.h"

// STROBE AND CLOCK MACROS
#define VFD_STROBE_START { uint8_t i; LPC_GPIO->CLR[ 1 ] = (1 << 14); for( i=0; i<48; i++ ) __NOP(); }
#define VFD_STROBE_STOP { uint8_t i; LPC_GPIO->SET[ 1 ] = (1 << 14); for( i=0; i<48; i++ ) __NOP(); }
#define VFD_START_BYTE		0b11111010 //I'm going to send you characters
#define VFD_COMMAND_BYTE	0b11111000 //commanding
#define VFD_CLOCK { uint8_t i; LPC_GPIO->CLR [ 1 ] = (1 << 15); for( i=0; i<48; i++ ) __NOP();  LPC_GPIO->SET [ 1 ] = (1 << 15); for( i=0; i<48; i++ ) __NOP(); }
#define VFD_DATA_HIGH LPC_GPIO-> SET [ 1 ] = (1 << 22); VFD_CLOCK
#define VFD_DATA_LOW LPC_GPIO-> CLR [ 1 ] = (1 << 22); VFD_CLOCK


typedef enum {
	NOTINITIALIZED,	//!< NOTINITIALIZED
	INITIALIZING,  	//!< INITIALIZING
	INITIALIZED,   	//!< INITIALIZED
	POWEREDOFF,    	//!< POWEREDOFF
	BUSY           	//!< BUSY
} eStatus;

typedef enum {
	ON,				//! Display on
	SLEEP,			//! Display sleep
	OFF				//! Display off
} ePowerstate;

typedef enum {
	INIT,			//! Initialize
	CLEAR			//! Clear the display
} eCommand;

typedef struct{
	eStatus VDFStatus;
	uint8_t x;
} VFD_Display;

void VFDInit(void);
void VFDWriteString(char*, int);
void VFDSendFiller(void);
uint8_t VFDSetPower(ePowerstate);
void VFDWriteChar(char);
uint8_t VFDSendCommand (eCommand);


#ifdef __cplusplus
}
#endif

#endif
