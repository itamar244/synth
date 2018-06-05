#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include <avr/pgmspace.h>

namespace synth {

struct MelodyContainer {
	const PGMArray melody;
	const PGMArray sections;
	const float speed;
};

} // namespace synth
