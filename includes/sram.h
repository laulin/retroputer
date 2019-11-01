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

#define BANK_0              1
#define BANK_1              2
#define BANK_0_AND_1        3
#define NO_BANK             0

#define READ_COMMAND        0x03
#define WRITE_COMMAND       0x02

#define ADDRESS_SIZE        3

#define READ_SRAM              0
#define WRITE_SRAM              1

void init_sram(void);
uint8_t check_sram_request(uint32_t address, uint32_t size);
uint8_t select_bank_sram(uint32_t address, uint32_t size);
void split_sram_request(uint32_t address, uint32_t size, uint32_t* b0_addr, uint32_t* b0_size, uint32_t* b1_addr, uint32_t* b1_size);
void address_to_array(uint32_t address, uint8_t* array);
uint8_t rw_bytes_23LC1024(uint8_t rw, uint8_t bank, uint32_t address, uint8_t* data, uint32_t size);
uint8_t rw_bytes_sram(uint8_t rw, uint32_t address, uint8_t* data, uint32_t size);
uint8_t write_bytes_sram(uint32_t address, uint8_t* data, uint32_t size);
uint8_t read_bytes_sram(uint32_t address, uint8_t* data, uint32_t size);

#endif // __SRAM_HEADER__