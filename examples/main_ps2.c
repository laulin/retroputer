#include "hal.h"
#include <stdint.h>
#include <util/delay.h>

// Test hardware UART

int main()
{
    init_timer();
    init_hw_uart(baudrate_115200);
    init_ps2();
    while (1)
    {
        if (key != 0)
        {
            hw_uart_write('a');
            key = 0;
        }
        _delay_ms(100);
    }
    return 0;
}