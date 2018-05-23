#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>

namespace synth {

struct MelodyContainer {
	using Sections = const std::vector<uint8_t>*;

	const uint8_t* melody;
	const uint16_t size;
	const float speed;
	Sections sections;
};

} // namespace synth
