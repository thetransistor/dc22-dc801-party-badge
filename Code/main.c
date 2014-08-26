/* ******
 author: d3c4f
 with help from:
    devino, nemus, yukaia, Isaac, and DC801
 shout outs to:
    sebseb7 ( github.com/sebseb7 ) - Who originally showed us the LPC1347 years ago, and organized some of the code base.
    cavehamster ( github.com/cavehamster) - Organized some of the Makefile, and pushed us to fastforward some of this work.
***** */

#include "main.h"
#include "core/inc/lpc13uxx_timer32.h"
#include "core/inc/lpc13uxx_gpio.h"
#include "drivers/general.h"
#include "drivers/buttons.h"
#include "drivers/ws2812b.h"
#include "drivers/vfd.h"
#include "libraries/vfdtext.h"

volatile uint32_t msTicks = 0;


void SysTick_Handler( void )
{
	// TODO: Verifiy SysTick is calculated correctly
	msTicks++;
}


void delay_ms( uint32_t ms )
{
	// Try not to use this...
	uint32_t now = msTicks;
	while( (msTicks-now) < ms );
}


uint32_t getMsTicks()
{
	return msTicks;
}


// STARTING EXECUTION... HACK ALL THE THINGS... EXTERMINATE.
int main( void )
{
	SystemCoreClockUpdate(); // Clock is set to 72Mhz
	SysTick_Config( SystemCoreClock/1000 );
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // clock to GPIO

	uint8_t aniDelay = 50; // msDelay for spinners animation. move to looping text obj later...
	uint32_t nextAni = msTicks + aniDelay;
	uint8_t posi = 0;
	uint8_t battStats;
/*
	uint8_t buttonStates;
*/
	uint8_t VFDBright	  = 0xFF;
/*
	uint8_t VFDBrightStep = 0x2A;
*/


	if( VFDGetStatus() != INITIALIZED ) VFDInit(); // Initialize the VFD

	char msgA[] =         "-blinkenlichten-";
	char msgB[] =         "rev. 0.0.0.1LATE";
	char msgC[] =         "See Ya Next Year";
	char msgD[] =         " woot, AwkHugs! ";
	char textBuffer01[] = "dc801smartbadger";

	char batteryStatus[10] = "battery:  ";

	VFDTextConfigure(
		0,			// Object Number
		textBuffer01, // Pointer to char array
		16,			// Number of chars to use
		0,			// Row number, 0 | 1
		0,			// Column to start on
		16,			// Width of Object (can be larger or smaller then # chars)
		150,		// Speed to update (in mS)
		GLITCH,	    // Object Style
		RUNNING,	// Object State
		0,			// Direction
		0);		    // Initial Loop Count
	VFDTextConfigure(
		1,			// Object Number
		batteryStatus, // Pointer to char array
		10,			// Number of chars to use
		1,			// Row number, 0 | 1
		2,			// Column to start on
		10,			// Width of Object (can be larger or smaller then # chars)
		150,		// Speed to update (in mS)
		NONE,	    // Object Style
		RUNNING,	// Object State
		0,			// Direction
		0);		    // Initial Loop Count

	// -------------------------------------------------------------------------
	// Infinity, Infinity
	while(1)
	{
		VFDTextUpdate(); // Update text 'objects'


		// ---------------------------------------------------------------------
		// Update the battery Status
		battStats = GetBatteryStatus();
		if( battStats == 0b00000011 ){
			batteryStatus[9] = 'D';
		} else if ( battStats == 0b00000001 ) {
			batteryStatus[9] = 'C';
		} else {
			batteryStatus[9] = 'B';
		}
		// ---------------------------------------------------------------------


		// ---------------------------------------------------------------------
		// Code for animation on top line
		if( msTicks >=  nextAni ){
			nextAni = msTicks + aniDelay;

			posi++;
			if( posi > 3 ) posi = 0;

			switch( posi ){
				case 0:
					VFDWriteChar2(1,0,'|');
					VFDWriteChar2(1,15,'|');
					break;
				case 1:
					VFDWriteChar2(1,0,'/');
					VFDWriteChar2(1,15,0x8C);
					break;
				case 2:
					VFDWriteChar2(1,0,'-');
					VFDWriteChar2(1,15,'-');
					break;
				case 3:
					VFDWriteChar2(1,0,0x8C);
					VFDWriteChar2(1,15,'/');
					break;
			}
		}
		// ---------------------------------------------------------------------


		// ---------------------------------------------------------------------
		// Code for debounced button(s) testing / VFD Brightness demo
		if( ButtonPressed(A) ){
			for( uint8_t z = 0; z < 16; z++ ) textBuffer01[z] = msgA[z];
/*
			if(VFDBright <= (0xFF - VFDBrightStep)) VFDBright += VFDBrightStep;
			VFDSetBrightness(VFDBright);
*/
		}
		if( ButtonPressed(B) ){
			for( uint8_t z = 0; z < 16; z++ ) textBuffer01[z] = msgB[z];
/*
			if(VFDBright >= (0x00 + VFDBrightStep)) VFDBright -= VFDBrightStep;
			VFDSetBrightness(VFDBright);
*/
		}
		if( ButtonPressed(C) ){
			for( uint8_t z = 0; z < 16; z++ ) textBuffer01[z] = msgC[z];
		}
		if( ButtonPressed(D) ){
			for( uint8_t z = 0; z < 16; z++ ) textBuffer01[z] = msgD[z];
		}

		if ( ButtonsPressed(A,B) ){
			VFDSendCommand(VFD_OFF);
		}
		if ( ButtonsPressed(C,D) && VFDGetStatus() == POWEREDOFF ){
			VFDSendCommand(VFD_ON);
			VFDSetBrightness(VFDBright); // Restore current brightness setting
		}
		// ---------------------------------------------------------------------

	}
}
