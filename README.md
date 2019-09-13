# retroputer

This repos is about source code for the retroputer arduino shield : https://easyeda.com/gignops/retro-computer

# Board

## WARNING

On V0 version - first batch - it is important to set GPIOA0-3 in input. Otherwish,
they will collide with D7-10.

This hardware bug was removed.

## Connections

D0  - PD0 : RX
D1  - PD1 : TX
D2  - PD2 : RX_DISPLAY
D3  - PD3 : TX_DISPLAY
D4  - PD4 : KB_DATA
D5  - PD5 : KB_CLOCK
D6  - PD6 : HP
D7  - PD7 : RAM0_SELECT_
D8  - PB0 : RAM1_SELECT_
D9  - PB1 : ROM0_SELECT_
D10 - PB2 : ROM1_SELECT_
D11 - PB3 : SPI MOSI
D12 - PB4 : SPI MISO
D13 - PB5 : SPI CLK

A0  - PC0 : unused
A1  - PC1 : INTB
A2  - PC2 : INTA
A3  - PC3 : IO_SELECT_
A4  - PC4 : I2C SDA
A5  - PC5 : I2C SCL
