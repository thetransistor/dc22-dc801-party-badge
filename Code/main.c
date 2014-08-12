/**
 *
 * @brief Example code for the dc801 ARM arm badge from defcon 22
 * @file main.c
 *
 * This is an example of what you can do with your defcon 22 dc801 badge.
 * Based on the pentarm13uxx project at https://github.com/sebseb7/pentarm13uxx
 *
 * Base vfd driver code by @d4rkm4tter
 *
 * @author @hamster
 *
 */

#include "main.h"
#include <stdio.h>

#include "drivers/vfd.h"
#include "core/inc/lpc13uxx_timer32.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
	msTicks++;
}

void delay_ms(uint32_t ms) {
	uint32_t now = msTicks;
	while ((msTicks-now) < ms);
}

int main(void) {

	char hack[] = 		"Hacking";
	char dots[] = 		"....";
	char carrier[] = 	"Hacking....        >CARRIER UP";
	char dc801[] = 		" -=[ DC 801 ]=- ";
	char hamster[] = 	"    @hamster";
	int i;

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	// clock to GPIO
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	// configure the two LEDs PINs as GPIO (they default to jtag)
	LPC_IOCON->TRST_PIO0_14  &= ~0x07;
	LPC_IOCON->TRST_PIO0_14  |= 0x01;


	VFDInit();

	while(1){
		VFDSendCommand(CLEAR);
		delay_ms(2000);

		for(i = 0; i < (sizeof(hack) - 1); i++){
			delay_ms(150);
			VFDWriteChar(hack[i]);
		}

		for(i = 0; i < (sizeof(dots) - 1); i++){
			delay_ms(400);
			VFDWriteChar(dots[i]);
		}
		delay_ms(500);

		VFDSendCommand(CLEAR);

		VFDWriteString(carrier, 1);
		delay_ms(3000);

		VFDSendCommand(CLEAR);

		VFDWriteString(dc801, 1);
		VFDSendFiller();
		VFDWriteString(hamster, 1);

		delay_ms(3000);


	}

	return(0);

}



