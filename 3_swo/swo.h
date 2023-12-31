#ifndef _SWO_H_
#define _SWO_H_
#include "stm32f4xx.h"

void SWO_init(uint8_t STM_port);
void SWO_putc(char c, uint8_t STM_port);

#endif
