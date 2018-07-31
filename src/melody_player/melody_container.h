#pragma once

#include <cstdint>
#include <vector>
#include "pgm_array.h"

namespace synth {

struct MelodyContainer {
	const PGMArray melody;
	const PGMArray sections;
	const float speed;
};

} // namespace synth
