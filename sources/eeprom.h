#ifndef __EEPROM_HEADER__
#define __EEPROM_HEADER__

#include <stdint.h>
#include "spi.h"
#include "error.h"

#define EEPROM_PAGE_NUMBER_PER_CHIP     512
#define EEPROM_PAGE_SIZE                256
#define EEPROM_CHIP_NUMBER              2
// 1024 pages of 256 bytes

#define EEPROM_COMMAND_READ             0x03
#define EEPROM_COMMAND_WRITE            0x02
#define EEPROM_COMMAND_WRITE_ENABLE     0x06
#define EEPROM_COMMAND_WRITE_DISABLE    0x04
#define EEPROM_COMMAND_READ_STATUS      0x05
#define EEPROM_COMMAND_PAGE_ERASE       0x42
#define EEPROM_COMMAND_CHIP_ERASE       0xB7

#define EEPROM_WIP_FLAG                 0x01

#define EEPROM_CHIP_0                   0
#define EEPROM_CHIP_1                   1

// required : SPI HAL must be init

void init_eeprom(void);
uint8_t is_eeprom_busy(uint16_t page);
uint8_t write_eeprom_page(uint8_t* bytes, uint16_t page);
uint8_t read_eeprom_page(uint8_t* bytes, uint16_t page);


#endif // __EEPROM_HEADER__