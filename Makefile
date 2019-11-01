example_spi: setup build_hal
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -I sources/ -c -o output/arduino/main_spi.o examples/main_spi.c
	avr-gcc -mmcu=atmega328p -L"$(shell pwd)/lib" -o output/arduino/main_spi.bin output/arduino/main_spi.o -lhal
	avr-objcopy -O ihex -R .eeprom output/arduino/main_spi.bin output/arduino/main_spi.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_spi.hex

example_ram: setup build_hal
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -I sources/ -c -o output/arduino/main_ram.o examples/main_ram.c
	avr-gcc -mmcu=atmega328p -L"$(shell pwd)/lib" -o output/arduino/main_ram.bin output/arduino/main_ram.o -lhal
	avr-objcopy -O ihex -R .eeprom output/arduino/main_ram.bin output/arduino/main_ram.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_ram.hex

example_uart: setup build_hal
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -I sources/ -c -o output/arduino/main_uart.o examples/main_uart.c
	avr-gcc -mmcu=atmega328p -L"$(shell pwd)/lib" -o output/arduino/main_uart.bin output/arduino/main_uart.o -lhal
	avr-objcopy -O ihex -R .eeprom output/arduino/main_uart.bin output/arduino/main_uart.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_uart.hex

example_ps2: setup build_hal
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -I sources/ -c -o output/arduino/main_ps2.o examples/main_ps2.c
	avr-gcc -mmcu=atmega328p -L"$(shell pwd)/lib" -o output/arduino/main_ps2.bin output/arduino/main_ps2.o -lhal
	avr-objcopy -O ihex -R .eeprom output/arduino/main_ps2.bin output/arduino/main_ps2.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_ps2.hex

system_check: setup build_hal
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -I sources/ -c -o output/arduino/check.o tests/check.c
	avr-gcc -mmcu=atmega328p -L"$(shell pwd)/lib" -o output/arduino/check.bin output/arduino/check.o -lhal
	avr-objcopy -O ihex -R .eeprom output/arduino/check.bin output/arduino/check.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/check.hex


build_sram_so:
	gcc -Wall -std=c11 -Dx86 -shared -o output/x86/sram.so -fPIC sources/mock_spi.c sources/sram.c
	gcc -Dx86 -E sources/sram.h > output/x86/sram.e

test: build_sram_so
	python3 tests/test_sram.py

build_hal: setup
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/spi.o sources/spi.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/sram.o sources/sram.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/port_expander.o sources/port_expander.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/hw_uart.o sources/hw_uart.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/hp.o sources/hp.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/timer.o sources/timer.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/eeprom.o sources/eeprom.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/ps2.o sources/ps2.c
	avr-ar -r "lib/libhal.a" output/arduino/*.o

setup:
	mkdir -p output/
	mkdir -p output/x86
	mkdir -p output/arduino
	mkdir -p lib

clean:
	rm -f output/arduino/*
	rm -f output/x86/*
	rm -f lib