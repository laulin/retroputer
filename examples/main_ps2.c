#include "hal.h"
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>

// Test hardware UART

int main()
{
    init_timer();
    init_hw_uart(baudrate_115200);
    init_ps2();
    uint8_t buffer[16] = {0};
    while (1)
    {
        if (key != 0)
        {
            //hw_uart_write('a');
            snprintf(buffer, 16, "0x%04x ", key);
            hw_uart_write_array(buffer, 7);
            key = 0;
        }
        _delay_ms(100);
    }
    return 0;
}