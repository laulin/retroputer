#include "spi.h"

// this is an hardware abstraction layer
// can't be unit tester !
// Please care on change, test on board

void init_spi(void)
{
    RAM0_SELECT_DDR |= RAM0_SELECT_OFFSET;
    RAM1_SELECT_DDR |= RAM1_SELECT_OFFSET;
    ROM0_SELECT_DDR |= ROM0_SELECT_OFFSET;
    ROM1_SELECT_DDR |= ROM1_SELECT_OFFSET;
    IO_SELECT_DDR |= IO_SELECT_OFFSET;
    SPI_MOSI_DDR |= SPI_MOSI_OFFSET;
    SPI_CLK_DDR |= SPI_CLK_OFFSET;
    // SPI_MISO_DDR is unchange, 0/input by default 

    SPCR = 1<<SPE | 1<<MSTR;
    SPSR = 1<<SPI2X;
}

