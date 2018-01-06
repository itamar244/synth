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
#include "tones.h"

#define SONG_SIZE(NAME)                                                        \
  sizeof(songs::NAME) / sizeof(songs::NAME[0])

namespace synth {
namespace songs {

#include "song_player/songs/the_small_jonathan.h"
#include "song_player/songs/seven_nation_army.h"

} // namespace songs
} // namespace synth
