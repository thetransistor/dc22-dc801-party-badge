/****************************************************************************
 *   $Id:: gpio.h 6172 2011-01-13 18:22:51Z usb00423                        $
 *   Project: NXP LPC13Uxx software example
 *
 *   Description:
 *     This file contains definition and prototype for GPIO.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __GPIO_H 
#define __GPIO_H

/* Includes ------------------------------------------------------------------- */
#include "LPC13Uxx.h"
#include "lpc_types.h"

#define CHANNEL0	0
#define CHANNEL1	1
#define CHANNEL2	2
#define CHANNEL3	3
#define CHANNEL4	4
#define CHANNEL5	5
#define CHANNEL6	6
#define CHANNEL7	7

#define PORT0		0
#define PORT1		1

#define GROUP0		0
#define GROUP1		1

void PIN_INT0_IRQHandler(void);
void PIN_INT1_IRQHandler(void);
void PIN_INT2_IRQHandler(void);
void PIN_INT3_IRQHandler(void);
void PIN_INT4_IRQHandler(void);
void PIN_INT5_IRQHandler(void);
void PIN_INT6_IRQHandler(void);
void PIN_INT7_IRQHandler(void);
void GINT0_IRQHandler(void);
void GINT1_IRQHandler(void);
void GPIOInit( void );
void GPIOSetPinInterrupt( uint32_t channelNum, uint32_t portNum, uint32_t bitPosi,
		uint32_t sense, uint32_t event );
void GPIOPinIntEnable( uint32_t channelNum, uint32_t event );
void GPIOPinIntDisable( uint32_t channelNum, uint32_t event );
uint32_t GPIOPinIntStatus( uint32_t channelNum );
void GPIOPinIntClear( uint32_t channelNum );
void GPIOSetGroupedInterrupt( uint32_t groupNum, uint32_t *bitPattern, uint32_t logic,
		uint32_t sense, uint32_t *eventPattern );
uint32_t GPIOGetPinValue( uint32_t portNum, uint32_t bitPosi );
void GPIOSetBitValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal );
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir );



/* GPIO style ------------------------------- */
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir);
void GPIO_SetValue(uint8_t portNum, uint32_t bitValue);
void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue);
uint32_t GPIO_ReadValue(uint8_t portNum);
void GPIO_IntCmd(uint8_t portNum, uint32_t bitValue, uint8_t edgeState);
FunctionalState GPIO_GetIntStatus(uint8_t portNum, uint32_t pinNum, uint8_t edgeState);
void GPIO_ClearInt(uint8_t portNum, uint32_t bitValue);


#endif /* end __GPIO_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
