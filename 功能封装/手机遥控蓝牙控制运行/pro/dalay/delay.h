#ifndef  _DELAY_H
#define  _DELAY_H

#include "stm32f10x.h"
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nus);

#endif
