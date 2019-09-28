#include "hal.h"
#include <stdint.h>
#include <util/delay.h>

// Test hardware UART

int main()
{
    init_spi();
    init_hw_uart(baudrate_115200);
    while(1)
    {
        hw_uart_write('a');
        _delay_ms(100);
    }
    return 0;
}