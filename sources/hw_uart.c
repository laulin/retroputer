#include "hw_uart.h"

const uint16_t BAUDRATE[14] = {
    416, //2400
    207, //4800
    103, // 9600
    68, // 14400
    51, //19200
    34, // 28800
    25, // 38400
    16, // 57600
    12, // 76800
    8, // 115200
    3, // 230400
    3, // 250000
    1, // 500000
    0 // 1000000
};

void init_hw_uart(uint32_t baudrate_index)
{
    uint16_t ubrr = BAUDRATE[baudrate_index];
    UBRR0H = (ubrr & 0xFF00) >>8;
    UBRR0L = ubrr & 0xFF;
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

uint8_t hw_uart_transmitted(void)
{
    return UCSR0A & (1<<UDRE0);
}

uint8_t hw_uart_received(void)
{
    return UCSR0A & (1<<RXC0);
}

uint8_t hw_uart_read(void)
{
    return UDR0;
}

void hw_uart_write(uint8_t byte)
{
    UDR0 = byte;
}

void hw_uart_wait_transmitted(void)
{
    while(!hw_uart_transmitted()) {}
}

void hw_uart_write_array(uint8_t* bytes, uint8_t size)
{
    uint8_t i=0;

    for(i=0; i<size; i++)
    {
        hw_uart_wait_transmitted();
        hw_uart_write(bytes[i]);
    }
}