#ifndef __PS2_HEADER__
#define __PS2_HEADER__

#include <stdint.h>
#include "error.h"

#ifndef x86
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

// need the timer module !

#define PS2_DATA_DDR        DDRD
#define PS2_CLK_DDR         DDRD

#define PS2_DATA_PIN        PIND
#define PS2_CLK_PIN         PIND

#define PS2_DATA_OFFSET     (1<<2)
#define PS2_CLK_OFFSET      (1<<3)

#define PS2_TIMEOUT         250
#define PS2_bit_size        11
#define PS2_BUFFER_SIZE     64

#define BREAK               0xF0
#define EXTENDED            0xE0
#define PAUSE               0xE1
#define NO_KEY              0x00

// https://techdocs.altium.com/display/FPGA/PS2+Keyboard+Scan+Codes

void init_ps2(void);
uint8_t ps2_get_byte(void);
uint8_t ps2_available_bytes(void);

#endif
