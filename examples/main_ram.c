#include "hal.h"
#include <util/delay.h>
#include <stdint.h>

// Test hardware of SPI device

int main()
{
    init_spi();
    init_sram();
    DDRC = 0x01; // use portc0 to validate RAM
    while(1)
    {
        PORTC = 0x01;
        _delay_ms(1);
        PORTC = 0x00;
        _delay_ms(1);

    }
    return 0;
}