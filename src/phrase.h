#pragma once

#include <cstdint>
#include <vector>
#include "audio.h"

namespace synth {

struct Phrase {
	Audio::NoteList notes;
	float length;

	inline const uint8_t Size() const {
		return notes.size();
	}
};

inline uint16_t PhraseLengthInMillis(const Phrase& phrase, float speed) {
	return 60 * phrase.length / speed;
}

} // namespace synth
