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
        uint8_t key = ps2_get_byte();
        if (key != NO_KEY)
        {
            //hw_uart_write('a');
            snprintf(buffer, 16, "0x%02x ", key);
            hw_uart_write_array(buffer, 7);
        }
    }
    return 0;
}