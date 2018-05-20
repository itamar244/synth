#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>

namespace synth {

struct Phrase {
	using Tones = std::vector<uint8_t>;

	Tones tones;
	uint8_t length;
};

} // namespace synth
