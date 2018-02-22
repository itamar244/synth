#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "song_player/pgm_song_parser.h"

namespace synth {

struct SongContainer {
	using Sections = const std::vector<uint8_t>&;

	const uint8_t* song;
	const uint16_t size;
	Sections sections;
};

} // namespace synth
