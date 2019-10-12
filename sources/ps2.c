#include "ps2.h"
#include "timer.h"

volatile uint32_t previous_time = 0;
volatile uint16_t bits = 0;
volatile uint8_t bit_counter = 0; 
volatile uint16_t key_buffer[PS2_BUFFER_SIZE];
volatile uint8_t key_buffer_tail = 0;
volatile uint8_t key_buffer_head = 0;

volatile uint16_t key=0x0000;

ISR(INT1_vect)
{
    // if(PS2_CLK_DDR & PS2_CLK_OFFSET == 0)// falling edge
    // {
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
            key = bits;
            bits = 0;
            bit_counter = 0;
        }

    // }
}

void init_ps2()
{
    // set data and clock as input
    PS2_DATA_DDR &= ~PS2_DATA_OFFSET;
    PS2_CLK_DDR &= ~PS2_CLK_OFFSET;

    // PCICR |= 0x04; //  = need for PCINT21
    // PCMSK2 |= 0x20; // =
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);//Interrupt on falling edge INT1
}