// helper to include all melodies
#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "melody_player/melody_container.h"

#define TONE_C   0
#define TONE_CS  1
#define TONE_D   2
#define TONE_DS  3
#define TONE_E   4
#define TONE_F   5
#define TONE_FS  6
#define TONE_G   7
#define TONE_GS  8
#define TONE_A   9
#define TONE_AS 10
#define TONE_B  11
#define TONE(NAME, OCTAVE) TONE_ ## NAME + (OCTAVE + 1) * 12

// NUMBER / quarter
#define Q32 1
#define Q16 2
#define Q8  4
#define Q4  8
#define Q2 16
#define Q1 32

#define MELODY(MELODY_NAME) const uint8_t MELODY_NAME[] PROGMEM
#define SECTIONS(MELODY_NAME) const uint8_t MELODY_NAME ## _SECTIONS[] PROGMEM

namespace synth {
namespace melodies {

#include "melody_player/melodies/another_brick_in_the_wall.h"
#include "melody_player/melodies/the_small_jonathan.h"
#include "melody_player/melodies/seven_nation_army.h"

} // namespace melodies
} // namespace synth

#undef TONE_C
#undef TONE_CS
#undef TONE_D
#undef TONE_DS
#undef TONE_E
#undef TONE_F
#undef TONE_FS
#undef TONE_G
#undef TONE_GS
#undef TONE_A
#undef TONE_AS
#undef TONE_B
#undef TONE
#undef MELODY
#undef SECTIONS
#undef Q32
#undef Q16
#undef Q8
#undef Q4
#undef Q2
#undef Q1
