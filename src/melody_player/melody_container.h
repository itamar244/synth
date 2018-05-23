#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "melody_player/parser.h"

namespace synth {

struct MelodyContainer {
	using Sections = const std::vector<uint8_t>*;

	const uint8_t* melody;
	const uint16_t size;
	Sections sections;
};

} // namespace synth
