#include "spi.h"

// this is an hardware abstraction layer
// can't be unit tester !
// Please care on change, test on board

void init_spi(void)
{
    // set IO as output
    RAM0_SELECT_DDR |= RAM0_SELECT_OFFSET;
    RAM1_SELECT_DDR |= RAM1_SELECT_OFFSET;
    ROM0_SELECT_DDR |= ROM0_SELECT_OFFSET;
    ROM1_SELECT_DDR |= ROM1_SELECT_OFFSET;
    IO_SELECT_DDR |= IO_SELECT_OFFSET;
    SPI_DDR |= SPI_MOSI_OFFSET | SPI_CLK_OFFSET;
    // SPI_MISO_DDR is unchange, 0/input by default 

    set_all_select();

    // define SPI master 
    SPCR = (1<<SPE) | (1<<MSTR);
    SPSR = 1<<SPI2X;
}

uint8_t read_write_spi (uint8_t data)
{
    // blocking R/W on SPI for one byte
    SPDR = data;
 
    // Wait for byte write/read
    while(!(SPSR & (1<<SPIF) ));
 
    // Return read data
    return SPDR ;
}

void write_bytes_spi (const uint8_t* data, uint8_t size)
{
    uint8_t i=0;
    for(i=0; i< size; i++)
    {
        // blocking R/W on SPI for one byte
        SPDR = data[i];
 
        // Wait for byte write/read
        while(!(SPSR & (1<<SPIF) ));
    }
}

void read_bytes_spi (uint8_t* data, uint8_t size)
{
    uint8_t i=0;
    for(i=0; i< size; i++)
    {
        // write useless data
        SPDR = 0x00;
 
        // Wait for byte write/read
        while(!(SPSR & (1<<SPIF) ));

        data[i] = SPDR;
    }
}

void clear_ram0_select(void)
{
    RAM0_SELECT_PORT &= ~RAM0_SELECT_OFFSET;
}

void set_ram0_select(void)
{
    RAM0_SELECT_PORT |= RAM0_SELECT_OFFSET;
}

void clear_ram1_select(void)
{
    RAM1_SELECT_PORT &= ~RAM1_SELECT_OFFSET;
}

void set_ram1_select(void)
{
    RAM1_SELECT_PORT |= RAM1_SELECT_OFFSET;
}

void clear_rom0_select(void)
{
    ROM0_SELECT_PORT &= ~ROM0_SELECT_OFFSET;
}

void set_rom0_select(void)
{
    ROM0_SELECT_PORT |= ROM0_SELECT_OFFSET;
}

void clear_rom1_select(void)
{
    ROM1_SELECT_PORT &= ~ROM1_SELECT_OFFSET;
}

void set_rom1_select(void)
{
    ROM1_SELECT_PORT |= ROM1_SELECT_OFFSET;
}

void clear_io_select(void)
{
    IO_SELECT_PORT &= ~IO_SELECT_OFFSET;
}

void set_io_select(void)
{
    IO_SELECT_PORT |= IO_SELECT_OFFSET;
}

void set_all_select(void)
{
    RAM0_SELECT_PORT |= RAM0_SELECT_OFFSET;
    RAM1_SELECT_PORT |= RAM1_SELECT_OFFSET;
    ROM0_SELECT_PORT |= ROM0_SELECT_OFFSET;
    ROM1_SELECT_PORT |= ROM1_SELECT_OFFSET;
    IO_SELECT_PORT |= IO_SELECT_OFFSET;
}