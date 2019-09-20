#ifndef __SPI_HEADER__
#define __SPI_HEADER__

#include <stdint.h>

#ifndef x86
#include <avr/io.h>

#define RAM0_SELECT_DDR         DDRD
#define RAM1_SELECT_DDR         DDRB
#define ROM0_SELECT_DDR         DDRB
#define ROM1_SELECT_DDR         DDRB
#define IO_SELECT_DDR           DDRC
#define SPI_DDR                 DDRB

#define RAM0_SELECT_PORT        PORTD
#define RAM1_SELECT_PORT        PORTB
#define ROM0_SELECT_PORT        PORTB
#define ROM1_SELECT_PORT        PORTB
#define IO_SELECT_PORT          PORTC

#define RAM0_SELECT_OFFSET      (1<<7)
#define RAM1_SELECT_OFFSET      (1<<0)
#define ROM0_SELECT_OFFSET      (1<<1)
#define ROM1_SELECT_OFFSET      (1<<2)
#define IO_SELECT_OFFSET        (1<<3)
#define SPI_MOSI_OFFSET         (1<<3)
#define SPI_MISO_OFFSET         (1<<4)
#define SPI_CLK_OFFSET          (1<<5)

#endif // not x86

void init_spi(void);
uint8_t read_write_spi (uint8_t data);
void write_bytes_spi (const uint8_t* data, uint8_t size);
void read_bytes_spi (uint8_t* data, uint8_t size);

void clear_ram0_select(void);
void set_ram0_select(void);
void clear_ram1_select(void);
void set_ram1_select(void);
void clear_rom0_select(void);
void set_rom0_select(void);
void clear_rom1_select(void);
void set_rom1_select(void);
void clear_io_select(void);
void set_io_select(void);
void set_all_select(void);

#endif //__SPI_HEADER__