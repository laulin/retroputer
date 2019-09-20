#include "sram.h"

void init_sram(void)
{
    // empty, to  be called for futur features
}

uint8_t check_sram_request(uint32_t address, uint32_t size)
{
    if(address+size-1 > SRAM_SIZE-1)
    {
        return SRAM_OUT_OF_RANGE;
    }
    return OK;
}

uint8_t select_bank_sram(uint32_t address, uint32_t size)
{
    // return the bank id(s) targeted by the address and the size
    if(check_sram_request(address, size) != OK)
    {
        return NO_BANK;
    }

    if(address <= SRAM_BANK_SIZE - 1)
    {
        //start is in bank 0
        if (address + size - 1 <= SRAM_BANK_SIZE - 1)
        {
            return BANK_0;
        }
        else
        {
            //banks overlap
            return BANK_0_AND_1;
        }
    }
    else
    {
        // start is in bank 1
        return BANK_1;
    }
}

void split_sram_request(uint32_t address, uint32_t size, uint32_t* b0_addr, uint32_t* b0_size, uint32_t* b1_addr, uint32_t* b1_size)
{
    // called if memory chuck overlaps both banks
    *b0_addr = address;
    *b0_size = (SRAM_BANK_SIZE - 1) - address;
    *b1_addr = 0x00000000;
    *b1_size = size - *b0_size;
}

void address_to_array(uint32_t address, uint8_t* array)
{
    array[0] = (address & 0xFF0000)>>16;
    array[1] = (address & 0xFF00)>>8;
    array[2] = (address & 0xFF);
}

uint8_t rw_bytes_23LC1024(uint8_t rw, uint8_t bank, uint32_t address, uint8_t* data, uint32_t size)
{
    switch(bank)
    {
        case BANK_0:
            clear_ram0_select(); break;
        case BANK_1:
            clear_ram1_select(); break;
        default:
            return KO;
    }

    // 24 bytes address
    uint8_t address_bytes[ADDRESS_SIZE];
    address_to_array(address, address_bytes);

    if(rw == READ_SRAM)
    {
        read_write_spi(READ_COMMAND);
        write_bytes_spi(address_bytes, ADDRESS_SIZE);
        read_bytes_spi(data, size);
    }
    else
    {
        read_write_spi(WRITE_COMMAND);
        write_bytes_spi(address_bytes, ADDRESS_SIZE);
        write_bytes_spi(data, size);
    }

    set_ram0_select();
    set_ram1_select();
    return OK;
}

uint8_t rw_bytes_sram(uint8_t rw, uint32_t address, uint8_t* data, uint32_t size)
{
    uint8_t banks = select_bank_sram(address, size);
    uint32_t b0_addr;
    uint32_t b0_size;
    uint32_t b1_addr;
    uint32_t b1_size;

    switch(banks)
    {
        case BANK_0:
        case BANK_1:
        {
            rw_bytes_23LC1024(WRITE_SRAM, banks, address, data, size);
            break;
        }
        case BANK_0_AND_1:
        {
            split_sram_request(address, size, &b0_addr, &b0_size, &b1_addr, &b1_size);
            rw_bytes_23LC1024(WRITE_SRAM, BANK_0, b0_addr, data, b0_size);
            rw_bytes_23LC1024(WRITE_SRAM, BANK_1, b1_addr, &data[b0_size], b1_size);
        }
        default:
            return SRAM_OUT_OF_RANGE;
    }
    return OK;
}

uint8_t write_bytes_sram(uint32_t address, uint8_t* data, uint32_t size)
{
    return rw_bytes_sram(WRITE_SRAM, address, data, size);
}

uint8_t read_bytes_sram(uint32_t address, uint8_t* data, uint32_t size)
{
    return rw_bytes_sram(READ_SRAM, address, data, size);
}