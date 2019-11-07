#include "hp.h"
#include <avr/io.h>

#define HP_DDR DDRD
#define HP_OFFSET (1 << 6)

void init_hp()
{
    // set PORTD6 as output
    HP_DDR |= HP_OFFSET;
    TCCR0A = 0x42; // toggle match OC0A , CTC
    TCCR0B = 0x00; // stopped
}

void sound_hp(uint16_t note)
{
    OCR0A = note & 0xFF;
    TCNT0 = 0;
    TCCR0B = note >> 8;
}

void mute_hp()
{
    TCCR0B = 0;
}