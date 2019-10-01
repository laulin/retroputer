#include "timer.h"

// source : https://www.locoduino.org/spip.php?article89

volatile uint32_t milisecond_ticks = 0;
volatile uint8_t divider = 0;

void init_timer(void)
{
    TCCR2A = 0b00000010; // CTC
    TCCR2B = 0b00000010; // 
    TIMSK2 = 0b00000010; // Interruption on match
    OCR2A = TIMER_COMPARE_VALUE;
    sei();
}

ISR(TIMER2_COMPA_vect) 
{
    divider++;
    if (divider >= TIMER_DIVIDER) 
    { 
        milisecond_ticks++;
        divider = 0;
    }
}

uint32_t milisecs(void)
{
    return milisecond_ticks;
}

void wait(uint32_t delay)
{
    uint32_t start_time = milisecond_ticks;

    while(milisecond_ticks < start_time + delay) {};
}