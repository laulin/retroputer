#ifndef __TIMER_HEADER__
#define __TIMER_HEADER__

#include <stdint.h>
#include "error.h"

#ifndef x86
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

#define TIMER_COMPARE_VALUE 199
#define TIMER_DIVIDER       10

void init_timer(void);
uint32_t milisecs(void);
void wait(uint32_t delay);

#endif
