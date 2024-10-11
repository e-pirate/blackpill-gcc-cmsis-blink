#ifndef _SWO_H_
#define _SWO_H_
#include "stm32f4xx.h"

#ifndef STLINK_FREQ
#define STLINK_FREQ 2000000
#endif

#define SWO_MAX_TRIES 1000

void SWO_init (const uint8_t port);
void SWO_disable (void);
uint8_t SWO_enabled (const uint8_t port);
int SWO_putc (char c, const uint8_t port);
ssize_t SWO_write (const uint8_t port, const char *s, size_t count);
int SWO_puts (const char *s, const uint8_t port);

#endif
