/**
 *
 * @brief Driver for the buttons
 * @file buttons.c
 *
 * Based on code developed by the pentarm13uxx project
 *
 */

#include <stdint.h>

#include "buttons.h"
#include "LPC13Uxx.h"


static uint16_t key_state;
static uint16_t key_press;


void buttonSample(void){

	static uint16_t ct0, ct1;
	
	uint16_t key_curr =	(LPC_GPIO->B0[16])|((LPC_GPIO->B1[19])<<1)|((LPC_GPIO->B0[1])<<2)|((LPC_GPIO->B1[20]<<3));

	uint16_t i = key_state ^ ~key_curr;
	
	ct0 = ~( ct0 & i );
	ct1 = ct0 ^ (ct1 & i);
	i &= ct0 & ct1;
	key_state ^= i;
	key_press |= key_state & i;
}
	

void buttonInit(void){

	LPC_GPIO->DIR[0] &= ~(1<<16);
	LPC_GPIO->DIR[1] &= ~(1<<19);
	LPC_GPIO->DIR[0] &= ~(1<<1);
	LPC_GPIO->DIR[1] &= ~(1<<20);

	LPC_IOCON->PIO0_16 	= (0 | 1<<5 | 1<<4);
	LPC_IOCON->PIO1_19 	= (0 | 1<<5 | 1<<4);
	LPC_IOCON->PIO0_1  	= (0 | 1<<5 | 1<<4);
	LPC_IOCON->PIO1_20  = (0 | 1<<5 | 1<<4);
}


uint16_t buttonGetPress( uint16_t key_mask ){
	key_mask &= key_press;                          // read key(s)
	key_press ^= key_mask;                          // clear key(s)
	return key_mask;
}

uint16_t buttonGetState( uint16_t key_mask ){
	return key_mask & key_state;
}

