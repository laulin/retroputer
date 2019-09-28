#ifndef __HW_UART_HEADER__
#define __HW_UART_HEADER__

#include <stdint.h>
#include "error.h"

#ifndef x86
#include <avr/io.h>
#endif

#define baudrate_2400       0
#define baudrate_4800       1
#define baudrate_9600       2
#define baudrate_14400      3
#define baudrate_19200      4
#define baudrate_28800      5
#define baudrate_38400      6
#define baudrate_57600      7
#define baudrate_76800      8
#define baudrate_115200     9
#define baudrate_230400     10
#define baudrate_250000     11
#define baudrate_500000     12
#define baudrate_1000000    13    

void init_hw_uart(uint32_t baudrate);

uint8_t hw_uart_transmitted(void);
uint8_t hw_uart_received(void);
uint8_t hw_uart_read(void);
void hw_uart_write(uint8_t byte) ;
void hw_uart_wait_transmitted(void);
void hw_uart_write_array(uint8_t* bytes, uint8_t size);

#endif // __HW_UART_HEADER__