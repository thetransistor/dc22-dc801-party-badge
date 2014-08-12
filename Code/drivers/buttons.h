#ifndef BUTTONS_H_
#define BUTTONS_H_

#define KEY_A (1<<0)
#define KEY_B (1<<1)
#define KEY_C (1<<2)
#define KEY_D (1<<3)


uint16_t buttonGetPress( uint16_t key_mask );
uint16_t buttonGetState( uint16_t key_mask );
void buttonSample(void);
void buttonInit(void);

#endif
