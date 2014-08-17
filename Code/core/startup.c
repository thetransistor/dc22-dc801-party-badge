#include <stdint.h>

extern unsigned int _end_stack;
extern unsigned int _end_text;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;

extern int main(void);
extern void SystemInit(void);

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SVC_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void DebugMon_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PendSV_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
/* LPC13Uxx specific interrupt handlers */
void PIN_INT0_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT1_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT2_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT3_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT4_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT5_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT6_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PIN_INT7_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void GINT0_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void GINT1_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void OSTIMER_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SSP1_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void I2C_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void CT16B0_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void CT16B1_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void CT32B0_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void CT32B1_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void SSP0_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USART_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USB_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USB_FIQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void ADC_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void WDT_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void BOD_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void FMC_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void OSCFAIL_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void PVTCIRCUIT_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));
void USBWakeup_IRQHandler(void) __attribute__ ((weak, alias ("Dummy_Handler")));

void Dummy_Handler(void);

void *vector_table[] __attribute__ ((section(".vectors"))) = {
	&_end_stack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,

	/* LPC13Uxx specific interrupt vectors */
	PIN_INT0_IRQHandler,
	PIN_INT1_IRQHandler,
	PIN_INT2_IRQHandler,
	PIN_INT3_IRQHandler,
	PIN_INT4_IRQHandler,
	PIN_INT5_IRQHandler,
	PIN_INT6_IRQHandler,
	PIN_INT7_IRQHandler,
	GINT0_IRQHandler,
	GINT1_IRQHandler,
	0,
	0,
	OSTIMER_IRQHandler,
	0,
	SSP1_IRQHandler,
	I2C_IRQHandler,
	CT16B0_IRQHandler,
	CT16B1_IRQHandler,
	CT32B0_IRQHandler,
	CT32B1_IRQHandler,
	SSP0_IRQHandler,
	USART_IRQHandler,
	USB_IRQHandler, 
	USB_FIQHandler,
	ADC_IRQHandler,
	WDT_IRQHandler,
	BOD_IRQHandler,
	FMC_IRQHandler,
	OSCFAIL_IRQHandler,
	PVTCIRCUIT_IRQHandler,
	USBWakeup_IRQHandler,
	0,
};

void Reset_Handler(void) {
	unsigned int *src, *dst;
	
	/* Copy data section from flash to RAM */
	src = &_end_text;
	dst = &_start_data;
	while (dst < &_end_data)
		*dst++ = *src++;

	/* Clear the bss section */
	dst = &_start_bss;
	while (dst < &_end_bss)
		*dst++ = 0;

	SystemInit();
	main();
}	

void Dummy_Handler(void) {
	while (1)
		;
}
