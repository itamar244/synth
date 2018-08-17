#pragma once

#include <melo/melo.h>

namespace synth {

using PhraseValue = const melo::PhraseValue;
using Phrase = PhraseValue*;

inline uint16_t PhraseLengthInMillis(const Phrase& phrase, float speed) {
	return 60 * phrase->length / speed;
}

} // namespace synth
