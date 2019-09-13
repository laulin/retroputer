#ifndef __SPI_HEADER__
#define __SPI_HEADER__

#include <avr/io.h>

#define RAM0_SELECT_DDR         DDRD
#define RAM1_SELECT_DDR         DDRB
#define ROM0_SELECT_DDR         DDRB
#define ROM1_SELECT_DDR         DDRB
#define IO_SELECT_DDR           DDRC
#define SPI_MOSI_DDR            DDRB
#define SPI_MISO_DDR            DDRB
#define SPI_CLK_DDR             DDRB

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

void init_spi(void);


#endif //__SPI_HEADER__