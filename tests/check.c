#include "hal.h"
#include <stdint.h>
#include <util/delay.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

// Test hardware UART
#define LINE_SIZE 80
uint8_t buffer[LINE_SIZE+1] = {0};

const uint8_t PROGMEM WELCOME[] = "\n*** Test System ***\n";
const uint8_t PROGMEM GOOD_BYE[] = "*******************\n";
const uint8_t PROGMEM RESULT_OK[] = "OK\n";
const uint8_t PROGMEM RESULT_KO[] = "KO\n";
const uint8_t PROGMEM RESULT_DONE[] = "DONE\n";
const uint8_t PROGMEM TEST_RAM_BANK_0[] = "Test RAM bank 0 : ";
const uint8_t PROGMEM TEST_RAM_BANK_1[] = "Test RAM bank 1 : ";
const uint8_t PROGMEM TEST_RAM_ALL[] = "Test RAM all : ";
const uint8_t PROGMEM TEST_SOUND[] = "Test sound ... ";
const uint8_t PROGMEM TEST_EEPROM_BANK_0[] = "Test EEPROM bank 0 : ";
const uint8_t PROGMEM WRITE_EEPROM_KO[] = "BAD WRITE\n";
const uint8_t PROGMEM READ_EEPROM_KO[] = "BAD READ\n";

void test_ram_bank_0(void)
{
    strncpy_P(buffer, TEST_RAM_BANK_0, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer)); 

    uint8_t data[4] = {0x00, 0xAA, 0x55, 0xFF};
    uint8_t read_data[4] = {0x00};
    write_bytes_sram(0x0000, data, 4);
    read_bytes_sram(0x0000, read_data, 4);

    if(memcmp(data, read_data, 4) != 0)
    {
        strncpy_P(buffer, RESULT_KO, LINE_SIZE);
        hw_uart_write_array(buffer, strlen(buffer)); 
        return;
    }

    strncpy_P(buffer, RESULT_OK, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));
}

void test_ram_bank_1(void)
{
    strncpy_P(buffer, TEST_RAM_BANK_1, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer)); 

    uint8_t data[4] = {0x00, 0xAA, 0x55, 0xFF};
    uint8_t read_data[4] = {0x00};
    write_bytes_sram(SRAM_BANK_SIZE, data, 4);
    read_bytes_sram(SRAM_BANK_SIZE, read_data, 4);

    if(memcmp(data, read_data, 4) != 0)
    {
        strncpy_P(buffer, RESULT_KO, LINE_SIZE);
        hw_uart_write_array(buffer, strlen(buffer)); 
        return;
    }

    strncpy_P(buffer, RESULT_OK, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));
}

void test_ram_bank_all(void)
{
    strncpy_P(buffer, TEST_RAM_ALL, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer)); 

    uint8_t data[128] = {0x00};
    uint8_t read_data[128] = {0x00};
    uint32_t i=0;
    for(i=0; i<128; i++)
    {
        data[i] = i & 0xFF;
    }

    for(i=0; i<SRAM_SIZE; i+= 128)
    {
        write_bytes_sram(i, data, 128);
        read_bytes_sram(i, read_data, 128);
        if(memcmp(data, read_data, 128) != 0)
        {
            strncpy_P(buffer, RESULT_KO, LINE_SIZE);
            hw_uart_write_array(buffer, strlen(buffer)); 
            return;
        }
    }    

    strncpy_P(buffer, RESULT_OK, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));
}

void test_sound(void)
{
    strncpy_P(buffer, TEST_SOUND, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));

    sound_hp(DO_4);
    _delay_ms(100);
    sound_hp(MI_4);
    _delay_ms(100);
    sound_hp(LA_4);
    _delay_ms(100);
    mute_hp();

    strncpy_P(buffer, RESULT_DONE, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));
}

void test_eeprom_bank_0(void)
{
    strncpy_P(buffer, TEST_EEPROM_BANK_0, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer)); 

    uint8_t data[EEPROM_PAGE_SIZE] = {0x00};
    data[0] = 0xAA;
    data[EEPROM_PAGE_SIZE-1] = 0x55;
    uint8_t read_data[EEPROM_PAGE_SIZE] = {0x00};
    while(is_eeprom_busy(0) != OK) {};
    write_eeprom_page(data, 0);
    while(is_eeprom_busy(0) != OK) {};
    read_eeprom_page(read_data, 0);
    

    if(memcmp(data, read_data, EEPROM_PAGE_SIZE) != 0)
    {
        strncpy_P(buffer, RESULT_KO, LINE_SIZE);
        hw_uart_write_array(buffer, strlen(buffer)); 
        return;
    }

    strncpy_P(buffer, RESULT_OK, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));
}


int main()
{
    init_spi();
    init_hw_uart(baudrate_115200);
    init_sram();
    init_hp();    
    
    strncpy_P(buffer, WELCOME, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));

    test_ram_bank_0();
    test_ram_bank_1();
    test_ram_bank_all();

    test_eeprom_bank_0();

    test_sound();

    strncpy_P(buffer, GOOD_BYE, LINE_SIZE);
    hw_uart_write_array(buffer, strlen(buffer));

    while(1)
    {
    }
    return 0;
}