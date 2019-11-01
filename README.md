# Retroputer

This repos is about source code for the retroputer arduino shield : https://easyeda.com/gignops/retro-computer

# Board

## Connections

* D0  - PD0 - P3.0  : RX
* D1  - PD1 - P3.1  : TX
* D2  - PD2 - P3.2  : RX_DISPLAY
* D3  - PD3 - P3.3  : TX_DISPLAY
* D4  - PD4 - P3.4  : KB_DATA
* D5  - PD5 - P3.5  : KB_CLOCK
* D6  - PD6 - P3.6  : HP
* D7  - PD7 - P3.7  : RAM0_SELECT_
* D8  - PB0 - P4.8  : RAM1_SELECT_
* D9  - PB1 - P4.9  : ROM0_SELECT_
* D10 - PB2 - P4.10 : ROM1_SELECT_
* D11 - PB3 - P4.11 : SPI MOSI
* D12 - PB4 - P4.12 : SPI MISO
* D13 - PB5 - P4.13 : SPI CLK

* A0  - PC0 - P2.0  : unused
* A1  - PC1 - P2.1  : INTB
* A2  - PC2 - P2.2  : INTA
* A3  - PC3 - P2.3  : IO_SELECT_
* A4  - PC4 - P2.4  : I2C SDA
* A5  - PC5 - P2.5  : I2C SCL

## EEPROM

Two chips of [EEPROM](https://en.wikipedia.org/wiki/EEPROM) - a technologie
used before Flash one exists - are present on the board. It is a Mcrochip 
[25LC1024](http://ww1.microchip.com/downloads/en/DeviceDoc/22064B.pdf), meaning
2Mbits (256 KBytes) of ROM is available. 

The 25LC1024 is composed of 512 pages of 256 bytes. By design, you will
have this constrains :

- Before doing any R/W action, you need to assert the EEPROM is not busy;
- You can read the enterly memory in one READ command if you want to;
- You can only write up to 256 bytes in 1 page at once. It takes 6ms;
- You can write one byte in one page, but it takes 6ms : the chip will update the enterly page;
- The chip is certified for 1M erase or write operations. Take care do not write or erase
  always at the sames pages.

Operations are done using the SPI bus and the chip select pins are D9 and D10.

Because there are two chips, you can design you system to parallelis read/write ops 
to improve performance. The write protection pin (/WP) and the hold pin (/HOLD) are 
not available.

##  SRAM

This kind of [RAM](https://en.wikipedia.org/wiki/Static_random-access_memory) retains 
data without being refresh periodically (not like DDR for example). Access is done using
the SPI bus and D7/D8 as chip select pins.

At the opposite, the component lifetime is independent of read/write ops; There is
not busy time after a write.

## Port expander

All GPIOs of ATMEGA328p are used for peripherals control. Because it is conveniant 
to have GPIO on such board, we add a port expander based on SPI bus. This way, it only
uses one pin of chip select. 

The [MCP32S17](http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf) fits 
this need and provides very powerful features :

- 16 I/Os pin splitted in two banks;
- two interrupts pin are connected to the ATMEGA.

The component interrupt can be foward to ATMEGA interrupt. You can have a fast reaction
on pin change. 

Keep in mind that port expander is always slower than *raw* GPIOs, even with a 
spi clock at 8Mhz.
