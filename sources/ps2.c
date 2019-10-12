#include "ps2.h"
#include "timer.h"

volatile uint32_t previous_time = 0;
volatile uint16_t bits = 0;
volatile uint8_t bit_counter = 0; 

volatile uint8_t key_buffer[PS2_BUFFER_SIZE];
volatile uint8_t key_buffer_length = 0;
volatile uint8_t key_buffer_head = 0;


ISR(INT1_vect)
{
    uint8_t bit = 0;
    uint32_t current_time = millisecs(); 

    if(current_time - previous_time > PS2_TIMEOUT)
    {
        bits = 0;
        bit_counter = 0;
    }
    previous_time = current_time;

    if (bit_counter > 0 && bit_counter <= 8)
    {
        bit = (PS2_DATA_PIN & PS2_DATA_OFFSET) != 0;
        bits |= bit << (bit_counter-1);

    }
    bit_counter++;

    if(bit_counter == PS2_bit_size)
    {
        if (key_buffer_length < PS2_BUFFER_SIZE)
        {
            key_buffer[key_buffer_head] = bits;
            key_buffer_head = (key_buffer_head + 1) & (PS2_BUFFER_SIZE-1);
            key_buffer_length++;
        }
        bits = 0;
        bit_counter = 0;
    }

}

uint8_t ps2_get_byte(void)
{
    if (key_buffer_length == 0)
    {
        return NO_KEY;
    }
    uint8_t tail = (key_buffer_head - key_buffer_length) & (PS2_BUFFER_SIZE - 1);
    uint8_t symbol = key_buffer[tail];
    key_buffer_length--;
    return symbol;
}

uint8_t ps2_available_bytes(void)
{
    return key_buffer_length;
}

void init_ps2()
{
    // set data and clock as input
    PS2_DATA_DDR &= ~PS2_DATA_OFFSET;
    PS2_CLK_DDR &= ~PS2_CLK_OFFSET;

    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);//Interrupt on falling edge INT1
}