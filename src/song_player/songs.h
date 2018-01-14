/**
 * includes all songs in namespace synth::songs.
 * each song is of type `const PROGMEM uint8_t[]` and followes this pattern -
 * ...(NUMBER_OF_TONES_IN_PHRASE, ...TONE, LENGTH)
 * TONE - 0 is C3, 23 is B4.
 * LENGTH - the number of 16ths of a quarter.
 *
 * for example: {0, 32, 2, 1, 3, 16} will sound as a puase of 4 quarters and
 * then C3 and E3 with the length of 2 quarters.
 */
#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

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

namespace synth {
namespace songs {

#include "song_player/songs/the_small_jonathan.h"
#include "song_player/songs/seven_nation_army.h"

} // namespace songs
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
#undef Q32
#undef Q16
#undef Q8
#undef Q4
#undef Q2
#undef Q1
