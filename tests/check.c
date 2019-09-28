#include "hal.h"
#include <stdint.h>
#include <util/delay.h>
#include <string.h>

// Test hardware UART

int main()
{
    init_spi();
    init_hw_uart(baudrate_115200);

    uint8_t *welcome = "\n*** Test System ***\n";
    hw_uart_write_array(welcome, strlen(welcome));
    while(1)
    {
    }
    return 0;
}