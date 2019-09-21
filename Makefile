build_spi: setup
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/spi.o sources/spi.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/main_spi.o sources/main_spi.c
	avr-gcc -mmcu=atmega328p -o output/arduino/main_spi.bin output/arduino/spi.o output/arduino/main_spi.o
	avr-objcopy -O ihex -R .eeprom output/arduino/main_spi.bin output/arduino/main_spi.hex

upload_spi: build_spi
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_spi.hex

build_sram_so:
	gcc -Wall -std=c11 -Dx86 -shared -o output/x86/sram.so -fPIC sources/mock_spi.c sources/sram.c
	gcc -Dx86 -E sources/sram.h > output/x86/sram.e

test: build_sram_so
	python3 tests/test_sram.py

build_hal: 
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/spi.o sources/spi.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/sram.o sources/sram.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/port_expander.o sources/port_expander.c
	avr-ar -r "output/arduino/libhal.a" output/arduino/*.o

setup:
	mkdir -p output/
	mkdir -p output/x86
	mkdir -p output/arduino

clean:
	rm -f output/arduino/*
	rm -f output/x86/*