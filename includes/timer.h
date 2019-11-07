#ifndef __TIMER_HEADER__
#define __TIMER_HEADER__

#include <stdint.h>
#include "error.h"

void init_timer(void);
uint32_t millisecs(void);
void wait(uint32_t delay);

#endif
