#include "hal.h"
#include <stdint.h>

// Test hardware of SPI device

int main()
{
    init_spi();
    #define DATA_SIZE 4
    const uint8_t DATA[DATA_SIZE] = {0x00, 0xAA, 0x55, 0xFF};

    while(1)
    {
        clear_ram0_select();
        read_write_spi(0xAA);
        set_ram0_select();

        clear_ram1_select();
        write_bytes_spi(DATA, DATA_SIZE);
        set_ram1_select();

        clear_rom0_select();
        read_write_spi(0x00);
        set_rom0_select();

        clear_rom1_select();
        read_write_spi(0x00);
        set_rom1_select();

        clear_io_select();
        read_write_spi(0x43);
        set_io_select();

    }
    return 0;
}