#include "eeprom.h"

#define EEPROM_COMMAND_READ 0x03
#define EEPROM_COMMAND_WRITE 0x02
#define EEPROM_COMMAND_WRITE_ENABLE 0x06
#define EEPROM_COMMAND_WRITE_DISABLE 0x04
#define EEPROM_COMMAND_READ_STATUS 0x05
#define EEPROM_COMMAND_PAGE_ERASE 0x42
#define EEPROM_COMMAND_CHIP_ERASE 0xB7

#define EEPROM_WIP_FLAG 0x01

#define EEPROM_CHIP_0 0
#define EEPROM_CHIP_1 1

void init_eeprom(void)
{
    // nothing to do
}

uint8_t get_chip(uint16_t page)
{
    // return 0 if the page range 0 to 511,
    // 1 if page range 512 to 1023,
    // else return -1
    if(page < EEPROM_PAGE_NUMBER_PER_CHIP)
    {
        return EEPROM_CHIP_0;
    }
    if(page < EEPROM_PAGE_NUMBER_PER_CHIP *  2)
    {
        return EEPROM_CHIP_1;
    }
    return EEPROM_OUT_OF_RANGE;
}

uint32_t get_local_address(uint16_t page)
{
    uint16_t modulo = EEPROM_PAGE_NUMBER_PER_CHIP -1;
    uint16_t local_page = page & modulo;
    uint32_t local_address = local_page * EEPROM_PAGE_SIZE;
    return local_address;
}

void set_rom_select(uint8_t chip)
{
    if(chip == EEPROM_CHIP_0)
    {
        set_rom0_select();
    }
    if(chip == EEPROM_CHIP_1)
    {
        set_rom1_select();
    }
}

void clear_rom_select(uint8_t chip)
{
    if(chip == EEPROM_CHIP_0)
    {
        clear_rom0_select();
    }
    if(chip == EEPROM_CHIP_1)
    {
        clear_rom1_select();
    }
}

uint8_t is_eeprom_busy(uint16_t page)
{
    // return BUSY if the page is not available, else OK
    // return EEPROM_OUT_OF_RANGE if the page is invalid
    uint8_t chip = get_chip(page);
    uint8_t status = 0x00;
    
    if (chip == EEPROM_OUT_OF_RANGE)
    {
        return EEPROM_OUT_OF_RANGE;
    }

    clear_rom_select(chip);
    read_write_spi(EEPROM_COMMAND_READ_STATUS);
    status = read_write_spi(0x00);
    set_rom_select(chip);

    if(status & EEPROM_WIP_FLAG)
    {
        return EEPROM_BUSY;
    }
    return OK;
}

uint8_t unlock_eeprom_write(uint16_t page)
{
    uint8_t chip = get_chip(page);
    
    if (chip == EEPROM_OUT_OF_RANGE)
    {
        return EEPROM_OUT_OF_RANGE;
    }

    clear_rom_select(chip);
    read_write_spi(EEPROM_COMMAND_WRITE_ENABLE);
    set_rom_select(chip);

    return OK;
}

uint8_t write_eeprom_page(uint8_t* bytes, uint16_t page)
{
    // bytes variable must contains at least 256 bytes
    uint8_t chip = get_chip(page);
    
    if (chip == EEPROM_OUT_OF_RANGE)
    {
        return EEPROM_OUT_OF_RANGE;
    }

    uint32_t local_address = get_local_address(page);
    unlock_eeprom_write(page);

    clear_rom_select(chip);
    read_write_spi(EEPROM_COMMAND_WRITE);
    write_24bits_address_spi(local_address);
    write_bytes_spi(bytes, EEPROM_PAGE_SIZE);
    set_rom_select(chip);

    return OK;

}

uint8_t read_eeprom_page(uint8_t* bytes, uint16_t page)
{
    // bytes variable must contains at least 256 bytes
    uint8_t chip = get_chip(page);
    
    if (chip == EEPROM_OUT_OF_RANGE)
    {
        return EEPROM_OUT_OF_RANGE;
    }

    uint32_t local_address = get_local_address(page);

    clear_rom_select(chip);
    read_write_spi(EEPROM_COMMAND_READ);
    write_24bits_address_spi(local_address);
    read_bytes_spi(bytes, EEPROM_PAGE_SIZE);
    set_rom_select(chip);

    return OK;

}