# Retroputer

The retroputer is a [Arduino shield](https://www.arduino.cc/en/Main/arduinoShields) that
is designed to recreate old style, 80's computer. Why ? Because it's easy to teach and 
to understand. 

This shield contains important components that let your imagination busy :

- 2 ROM chips, 2Mb (256KB)
- 2 RAM chips, 2Mb (256KB)
- 1 port expander with 16 I/0
- 4 leds 
- 1 buzzer
- 1 PS2 plug

Regarding actual hardware, it could appear to be unusable. But keep in mind that facts :

- Currently one web page can easily raise over 30MB of RAM, the same amount of RAM need to run Windows 95. 
- [Acorn MOS](https://en.wikipedia.org/wiki/Acorn_MOS) version 0 and 1 use only 16KiB of ROM
- The [Amiga 600](https://en.wikipedia.org/wiki/Amiga_600) was designed with 7.16Mhz Motorola [68000](https://en.wikipedia.org/wiki/Motorola_68000) and 1 MByte of RAM. 

Another important point is about the Hardware Abstraction Layer you can find in this 
repository. Even if it is an Arduino Shield, the library is coded in pure C, without any
link with Arduino IDE. The reason is simple : you will learn how to do bare meetal developpement ! All you need is :

- Install gcc-avr 
- Install binutils-avr 
- Install avr-libc
- Install avrdude
- RTFM (Read The Fabulous Manual) that is provide by Microchip (Atmel) : the [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

Now, let me give you some idea of project you may do :

- a small computer with home made retro games
- a low profile virtual machine
- hacking challenge
- brain teaser :)

# Board

## PCB

You can find the PCB and the schematics in my [EASYEDA project's page](https://easyeda.com/gignops/retro-computer). 

To EASYEDA is in business with JLCPCB and you can easily order you PCB. Then order
components (CF Bill Of Material), build the shield and it's over !

No SMD component is used to make easy to build and repaire.

## Bill Of Materials

- 1x MCP23S17 (DIP)
- 1x 28 pins DIP supports
- 2x 25LC1024 (DIP)
- 2x 23LC1024 (DIP)
- 4x 8 pins DIP supports
- 4x 3mm leds (ex : MCL034RHC)
- 1x buzzer KX1205
- 7x 100nf capacitor (ex :C320C104K5R5TA)
- 1x BS170 TO-92
- 1x PS2 (ex: TM 0508 mini din)
- 3x 40 pin male header 2.54mm


## Connections

- D0  - PD0 - P3.0  : RX
- D1  - PD1 - P3.1  : TX
- D2  - PD2 - P3.2  : RX_DISPLAY
- D3  - PD3 - P3.3  : TX_DISPLAY
- D4  - PD4 - P3.4  : KB_DATA
- D5  - PD5 - P3.5  : KB_CLOCK
- D6  - PD6 - P3.6  : HP
- D7  - PD7 - P3.7  : RAM0_SELECT_
- D8  - PB0 - P4.8  : RAM1_SELECT_
- D9  - PB1 - P4.9  : ROM0_SELECT_
- D10 - PB2 - P4.10 : ROM1_SELECT_
- D11 - PB3 - P4.11 : SPI MOSI
- D12 - PB4 - P4.12 : SPI MISO
- D13 - PB5 - P4.13 : SPI CLK
- A0  - PC0 - P2.0  : unused
- A1  - PC1 - P2.1  : INTB
- A2  - PC2 - P2.2  : INTA
- A3  - PC3 - P2.3  : IO_SELECT_
- A4  - PC4 - P2.4  : I2C SDA
- A5  - PC5 - P2.5  : I2C SCL

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

The [23LC1024](https://www.pjrc.com/teensy/23LC1024.pdf) is a 1Mbits SRAM chip. Two 
chips are present on the board. This means 256KBytes of RAM are available.

At the opposite, the component lifetime is independent of read/write ops; There is
not busy time after a write. Each byte can be read/write independantly (no page).

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

Four leds are connected to PORTA4 to PORTA7. 

## PS2 connector

As user input, you can plug a PS2 keyboard. Using interrupt of the ATMEGA, you can
efficiently get touch pressed. 

Let's talk about PS2 protocol/link. The PS2 plug uses four wires to control the keyboard :

- VCC at 5v
- GND
- Clock
- Data

Clock and data compose a serial synchronous, 8 bits link; Like RS232,
a start bit and two stop bits are used to delimit frame. So 11 bits are used for the 
transmission. Typically clock frequency is between 10 to 16 KHz. The clock is generated 
by the device (the keyboard here).

For more information about PS2 codes, you my read the [altrium PS2 page](https://techdocs.altium.com/display/FPGA/PS2+Keyboard+Scan+Codes).


## Buzzer

To make sound, a square signal can be generated on the pin D6. Easy and so retro !

## Sofware Serial UART

A four pins plug is prevent to connect a [Nextion display](https://nextion.tech/). It 
is a serial base display, easy to use.

No implementation in HAL yet.

## I2C

Two I2C plugs are available. One of them is specially designed to host a RTC clock.

No implementation in HAL yet.

# Hardware Abstraction Layer

This minimal implementation allows you to start quickly. But it is important to
understand what happen under the hood ... you may have another point of you an create
a better implementation one :)

## Install

```bash
$ make build_hal
$ sudo make install
```

## Compile and link HAL

For compiling :

```
avr-gcc -mmcu=atmega328p -I /usr/local/include/retroputer/hal -c -o foobar.o foobar.c
```

For linking :

```
avr-gcc -mmcu=atmega328p -L"/usr/local/lib/retroputer/hal" -o foobar.bin foobar.o -lhal
```

## SPI

The SPI module is the base of many other modules :

- EEPROM
- SRAM
- Port expander

For this reason, the function *init_spi()* must be called before any other *init_xxx()*.

- *init_spi()* setup the spi hardare device. It set SPI at 8MHz clock, mode 0.
- *read_write_spi()* is the basic function to read and write a byte. 
- *write_bytes_spi()* writes a byte array. Can write up to 0xFFFF bytes. 
- *read_bytes_spi()* reads a byte array. Can read up to 0xFFFF bytes. 
- *clear_XXXX_select()* clear the related chip select pin to enable the device.
- *set_XXXX_select()* set the related chip select pin to disable the device.
- *write_24bits_address_spi()* is a conveniant function to push 3 bytes, ofently used for address.

## SRAM

The SRAM module manages both RAM chips. The addresses are continuous :

- 0x00000 to 0x1FFFF is managed by chip 0 (RAM0)
- 0x20000 to 0x3FFFF is managed by chip 1 (RAM1)

Pro tips : the internal ATMEGA328 RAM is faster than SRAM modules.

- *init_sram()* initialize the SRAM communication. Need *init_spi()* to be called previously.
- *write_bytes_sram()* writes an array of bytes at specific address.
- *read_bytes_sram()* reads an array of bytes at specific address.

## EEPROM

The EEPROM module manages both EEPROM chips. The pages are continuous :

- 0 to 511 is managed by chip 0 (EEPROM0)
- 512 to 1023 is managed by chip 1 (EEPROM1)

- *init_sram()* initialize the SRAM communication. Need *init_spi()* to be called previously.
- *write_bytes_sram()* writes an array of bytes at specific address.
- *read_bytes_sram()* reads an array of bytes at specific address.


- *init_eeprom()* initialize the EEPROM communication. Need *init_spi()* to be called previously.
- *is_eeprom_busy()* checks if a page is available for operations.
- *write_eeprom_page()* writes page (256 bytes) enterly.
- *read_eeprom_page()* reads a page (256 bytes) enterly.



