#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>

namespace synth {

struct SongContainer {
	const uint8_t* song;
	const uint16_t size;
	const std::vector<uint8_t>& sections;
};

} // namespace synth
