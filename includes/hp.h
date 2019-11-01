#ifndef __HP_HEADER__
#define __HP_HEADER__

#include <stdint.h>
#include "error.h"

#ifndef x86
#include <avr/io.h>

#define HP_DDR          DDRD

#endif // x86

#define HP_OFFSET       (1<<6)

#define clock_div_1024  5
#define clock_div_256   4
#define clock_div_64    3
#define clock_div_8     2

// https://fr.wikipedia.org/wiki/Note_de_musique
#define DO_4 (clock_div_256<<8 | 119) // 261,63 
#define RE_4 (clock_div_256<<8 | 106) // 293,66  
#define MI_4 (clock_div_256<<8 | 94) // 329,63  
#define FA_4 (clock_div_256<<8 | 89) // 349,23  
#define SOL_4 (clock_div_256<<8 | 79) // 392,00 
#define LA_4 (clock_div_256<<8 | 70) // 440,00 
#define SI_4 (clock_div_64<<8 | 253) // 493,88 

void init_hp();

void sound_hp(uint16_t note);

void mute_hp();


#endif // __HP_HEADER__