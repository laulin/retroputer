#ifndef __EEPROM_HEADER__
#define __EEPROM_HEADER__

#include <stdint.h>
#include "spi.h"
#include "error.h"

#define EEPROM_PAGE_NUMBER_PER_CHIP     512
#define EEPROM_PAGE_SIZE                256
#define EEPROM_CHIP_NUMBER              2
// 1024 pages of 256 bytes

// required : SPI HAL must be init

void init_eeprom(void);
uint8_t is_eeprom_busy(uint16_t page);
uint8_t write_eeprom_page(uint8_t* bytes, uint16_t page);
uint8_t read_eeprom_page(uint8_t* bytes, uint16_t page);


#endif // __EEPROM_HEADER__