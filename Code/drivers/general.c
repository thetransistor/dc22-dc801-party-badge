// authored by: d3c4f

#include "general.h"
static void __attribute__ ((constructor)) InitializeDBGLED( void );
static void __attribute__ ((constructor)) InitializeBattStats( void );


// Set rear debug LED as an output
static void InitializeDBGLED()
{
    // Set as GPIO, reset all options
    LPC_IOCON->PIO1_24	= (0 | 1<<3);	// Rear Debug LED
    // Set as an output, and toggle from initial state
    LPC_GPIO->DIR[1] |= (1<<24);	   // Rear Debug LED
    //LPC_GPIO->NOT[1] = 1<<24; // Toggle the LED from it's initial state
    DebugLEDOff();
}


// Turn the Debug LED On
uint8_t DebugLEDOn()
{
    LPC_GPIO->SET[1] = ( 1<<24 );
    return 0;
}


// Turn the Debug LED Off
uint8_t DebugLEDOff()
{
    LPC_GPIO->CLR[1] = ( 1<<24 );
    return 0;
}


// Initialize the battery charger status lines
static void InitializeBattStats()
{
    // Set buttons as GPIO, Int PU Res
    LPC_IOCON->PIO0_21	= (0 | 1<<4); // Stat1
    LPC_IOCON->PIO0_5	= (0 | 1<<8); // Stat2
        // Stat 2 doesn't work
        // It needs a PU res. and mCU doesn't have a built-in one, and we didn't add one...
        // Don't worry, it still charges / protects / detects errors as intended.
        // We just loose the ability to check for errors from code. :S
    LPC_IOCON->PIO0_3	= (0 | 1<<3); // Work around for Stat2 being FUBAR. Check the USB 5v Line. :)

    // Set modes to input
    LPC_GPIO->DIR[0] &= ~(1<<21); // Stat1
    LPC_GPIO->DIR[0] &= ~(1<<5);  // Stat2
    LPC_GPIO->DIR[0] &= ~(1<<3);  // Stat2 work around, USB_VBUS
}


// Return the battery status
uint8_t GetBatteryStatus()
{
    uint8_t temp = 0;

    //temp = temp | (LPC_GPIO->PIN[0] & (0x1<<5)); // Stat2 line
    if( LPC_GPIO->PIN[0] & (0x1<<3) ){
        temp = temp | 0b00000001; // USB_VBUS line
    }
    if( LPC_GPIO->PIN[0] & (0x1<<21) ){
        temp = temp | 0b00000010; // Stat 2
    }

      /*
        return values
        0b00000011 -> Done Charging
        0b00000001 -> Charging over USB
        0b00000010 -> Not charging, Battery
        0b00000000 -> Not charging, Battery
      */
    return temp;
}
