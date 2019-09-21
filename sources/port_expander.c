#include "port_expander.h"

void write_byte_port_expander(uint8_t address, uint8_t value)
{
    clear_io_select();
    read_write_spi(MSB_ADDR | WRITE_MASK);
    read_write_spi(address);
    read_write_spi(value);
    set_io_select();
}

uint8_t read_byte_port_expander(uint8_t address)
{
    uint8_t value = 0;
    clear_io_select();
    read_write_spi(MSB_ADDR | READ_MASK);
    read_write_spi(address);
    value = read_write_spi(0x00);
    set_io_select();

    return value;
}

void init_port_expander(void)
{
    // set LED pins as output
    write_byte_port_expander(IODIRA, IODIRA_VALUE);
}

void set_led(uint8_t index)
{
    uint8_t olata = 0x00;

    olata = read_byte_port_expander(OLATA);
    olata |= 0x10 << index;
    write_byte_port_expander(OLATA, olata);
}

void clear_led(uint8_t index)
{
    uint8_t olata = 0x00;

    olata = read_byte_port_expander(OLATA);
    olata &= ~(0x10 << index);
    write_byte_port_expander(OLATA, olata);
}

void toggle_led(uint8_t index)
{
    uint8_t olata = 0x00;

    olata = read_byte_port_expander(OLATA);
    olata ^= 0x10 << index;
    write_byte_port_expander(OLATA, olata);
}

