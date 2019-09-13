build_spi: setup
	# need apt install gcc-avr binutils-avr avr-libc avrdude
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/spi.o sources/spi.c
	avr-gcc -Os -std=c11 -DF_CPU=16000000UL -mmcu=atmega328p -c -o output/arduino/main_spi.o sources/main_spi.c
	avr-gcc -mmcu=atmega328p -o output/arduino/main_spi.bin output/arduino/spi.o output/arduino/main_spi.o
	avr-objcopy -O ihex -R .eeprom output/arduino/main_spi.bin output/arduino/main_spi.hex

upload_spi:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:output/arduino/main_spi.hex

setup:
	mkdir -p output/
	mkdir -p output/x86
	mkdir -p output/arduino

clean:
	rm output/arduino/*
	rm output/x86/*