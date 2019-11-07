#ifndef __PS2_HEADER__
#define __PS2_HEADER__

#include <stdint.h>
#include "error.h"

// need the timer module !

#define BREAK               0xF0
#define EXTENDED            0xE0
#define PAUSE               0xE1
#define NO_KEY              0x00

// https://techdocs.altium.com/display/FPGA/PS2+Keyboard+Scan+Codes

void init_ps2(void);
uint8_t ps2_get_byte(void);
uint8_t ps2_available_bytes(void);

#endif
