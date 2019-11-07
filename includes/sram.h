#ifndef __SRAM_HEADER__
#define __SRAM_HEADER__

#include <stdint.h>
#include "spi.h"
#include "error.h"

// required : SPI HAL must be init

// The target chip is the 23LC104, a 1Mbit SRAM chip (128KB x 8).
// Designated RAM0 and RAM1, the memory space is here linear :
// running out of RAM0 will go to RAM1.

#define SRAM_BANK_SIZE      0x20000 // 128KB
#define SRAM_BANK_NUMBER    2
#define SRAM_SIZE           (SRAM_BANK_SIZE * SRAM_BANK_NUMBER)

void init_sram(void);
uint8_t write_bytes_sram(uint32_t address, uint8_t* data, uint32_t size);
uint8_t read_bytes_sram(uint32_t address, uint8_t* data, uint32_t size);

#endif // __SRAM_HEADER__