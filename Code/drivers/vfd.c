/**
 *
 * @brief Driver for the VFD display
 * @file vfd.c
 *
 * Based on code developed by @d4rkm4tter
 *
 */


#include "vfd.h"
#include <string.h>


/**
 * @brief Initialize the VFD display
 */
void VFDInit(void) {
	// TODO: Check initialization state

	// Outputs
	LPC_GPIO->DIR[PORT1] |= (1<<24);	// Rear LED
	LPC_GPIO->DIR[PORT0] |= (1<<7);		// RGB Shift Reg. Data
	LPC_GPIO->DIR[PORT0] |= (1<<4);		// VFD Power
	LPC_GPIO->DIR[PORT1] |= (1<<14);	// VFD Strobe
	LPC_GPIO->DIR[PORT1] |= (1<<15);	// VFD Clock
	LPC_GPIO->DIR[PORT1] |= (1<<22);	// VFD Data
	
	ssp1Init();
	
	VFD_STROBE_STOP;
	
//	VFDSendCommand(0b00001111);
	VFDSendCommand(INIT);
	
	VFDSetPower(ON);

}

/**
 * @brief Set display brightness
 * @param percent amount in percent
 * @todo implement function
 */
void setBrightness(int percent){
	//byte: 0011 BR3 BR2 BR1 BR0
	//6.25% increment - 1111 to 0000

}

/**
 * @brief Set the power state of the VFD
 * @return VFD status
 */
uint8_t VFDSetPower(ePowerstate newState) {

	if (newState == ON) {
		LPC_GPIO->CLR[PORT0] = 1<<4; //>...>...// Turn on the VFD Power
		
		// TODO: Update the VFD Status

	} else if(newState == SLEEP) {
		LPC_GPIO->SET[PORT0] = 1<<4;//>...>...// Turn off the VFD Power
		// TODO: Update the VFD Status

	} else if(newState == OFF) {
		LPC_GPIO->SET[PORT0] = 1<<4;//>...>...// Turn off the VFD Power
		// TODO: Update the VFD Status
	}

	return 0;

}


/**
 * @brief Send a command to the display
 * @param command
 * @return to be implemented
 */
uint8_t VFDSendCommand(eCommand command) {

	VFD_STROBE_START;
	sspSend(VFD_COMMAND_BYTE);

	switch(command){
		case CLEAR:
			sspSend(1);
			break;
		case INIT:
			sspSend(0b00001111);
			break;
		default:
			break;

	}
	VFD_STROBE_STOP;

	return 0;
}


/**
 * @brief Write a string to the display
 * @param str the string to write, null terminated
 * @param filler whether to send the line filler
 */
void VFDWriteString(char* str, int filler){

	int len = strlen(str);

	for(int i = 0; i< len; i++){
		if(i == 16 && filler == 1){
			VFDSendFiller();
		}
		VFDWriteChar(str[i]);
	}
	
}

/**
 * @brief Fills in the end of the display buffer
 *
 * Think about the buffer like 1 big ass 80 byte buffer that only shows you the first
 * 16 bytes and the middle 41-57 bytes, aka the left side of it. Not cool bro, not cool at all.
 * The point is, make it work with padding for stuff somehow.
 *
 */
void VFDSendFiller(void){

	for(int i = 0; i < 24; i++){
		VFDWriteChar(' ');
	}

}

/**
 * @brief Send a char to the display
 * @param newChar
 */
void VFDWriteChar(char newChar){

	VFD_STROBE_START;
	sspSend(VFD_START_BYTE);
	sspSend(newChar);
	VFD_STROBE_STOP;

}


