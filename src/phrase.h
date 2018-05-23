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

inline uint16_t PhraseLengthInMillis(const Phrase& phrase, float speed) {
	return 60 * phrase.length / speed;
}

} // namespace synth
