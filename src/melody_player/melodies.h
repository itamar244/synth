// includes all melodies in namespace synth::melodies.
// each melody is of type `const PROGMEM uint8_t[]` and followes this pattern -
// ...(NUMBER_OF_NOTES_IN_PHRASE, ...NOTE, LENGTH)
// NOTE - 0 is C3, 23 is B4.
// LENGTH - the number of 16ths of a quarter.
//
// for example: {0, 32, 2, 1, 3, 16} will sound as a puase of 4 quarters and
// then C3 and E3 with the length of 2 quarters.
#pragma once

#include <initializer_list>
#include <string>
#include "melodies_creator.h"
#include "melody_container.h"

namespace synth {
namespace melodies {

const std::initializer_list<const std::string> kMelodyNames = {
	"The Small Jonathan",
	"Seven Nation Army",
	"The Wall",
};

#define CONTAINER(NAME, SPEED)                                                 \
	MelodyContainer{                                                             \
		{ NAME, sizeof(NAME) / sizeof(NAME[0]) },                                  \
		{                                                                          \
			NAME ## _SECTIONS,                                                       \
			sizeof(NAME ## _SECTIONS) / sizeof(NAME ## _SECTIONS[0]),                \
		},                                                                         \
		SPEED,                                                                     \
	}

inline MelodyContainer GetContainer(const std::string& name) {
	if (name == "The Small Jonathan") {
		return CONTAINER(THE_SMALL_JONATHAN, 1);
	}
	if (name == "Seven Nation Army") {
		return CONTAINER(SEVEN_NATION_ARMY, 1);
	}
	if (name == "The Wall") {
		return CONTAINER(ANOTHER_BRICK_IN_THE_WALL, 0.8);
	}

	return {{nullptr, 0}, {nullptr, 0}, 0};
}

#undef CONTAINER

} // namespace melodies
} // namespace synth
