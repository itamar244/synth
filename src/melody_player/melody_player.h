// MelodyPlayer implements both Player And MelodyParser for parsing
// progmem melodies from `synth::melodies` and play them
#pragma once

#include <fstream>
#include <melo/melo.h>
#include <melo/phrase.h>
#include "player.h"

namespace synth {

class MelodyPlayer : public Player {
	using Phrase = melo::Phrase;

public:
	MelodyPlayer(std::ifstream& file);

	inline float phrase_length() const {
		return 60 * phrase_.length / speed_;
	}

protected:
	PLAYER_CALLBACKS_INHERIT

	melo::Module module_;
	melo::SectionWalker walker_;
	Phrase phrase_;
	const float speed_;
};

} // namespace synth
