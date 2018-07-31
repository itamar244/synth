// helper to include all melodies
#pragma once

#include <cstdint>
#include <vector>
#include "melody_container.h"

#define NOTE_C   0
#define NOTE_CS  1
#define NOTE_D   2
#define NOTE_DS  3
#define NOTE_E   4
#define NOTE_F   5
#define NOTE_FS  6
#define NOTE_G   7
#define NOTE_GS  8
#define NOTE_A   9
#define NOTE_AS 10
#define NOTE_B  11
#define NOTE(NAME, OCTAVE) NOTE_ ## NAME + (OCTAVE + 1) * 12

// NUMBER / quarter
#define Q32 1
#define Q16 2
#define Q8  4
#define Q4  8
#define Q2 16
#define Q1 32

#define MELODY(MELODY_NAME) constexpr uint8_t MELODY_NAME[]
#define SECTIONS(MELODY_NAME) constexpr uint8_t MELODY_NAME ## _SECTIONS[]

namespace synth {
namespace melodies {

#include "melodies/another_brick_in_the_wall.h"
#include "melodies/the_small_jonathan.h"
#include "melodies/seven_nation_army.h"

} // namespace melodies
} // namespace synth

#undef NOTE_C
#undef NOTE_CS
#undef NOTE_D
#undef NOTE_DS
#undef NOTE_E
#undef NOTE_F
#undef NOTE_FS
#undef NOTE_G
#undef NOTE_GS
#undef NOTE_A
#undef NOTE_AS
#undef NOTE_B
#undef NOTE
#undef MELODY
#undef SECTIONS
#undef Q32
#undef Q16
#undef Q8
#undef Q4
#undef Q2
#undef Q1
