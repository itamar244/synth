#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "audio.h"

namespace synth {

struct Phrase {
	Audio::NoteList notes;
	uint8_t length;

	inline const uint8_t Size() const {
		return notes.size();
	}
};

inline uint16_t PhraseLengthInMillis(const Phrase& phrase, float speed) {
	return 60 * phrase.length / speed;
}

} // namespace synth
