// MelodyPlayer implements both Player And MelodyParser for parsing
// progmem melodies from `synth::melodies` and play them
#pragma once

#include <fstream>
#include <melo/evaluator/module.h>
#include "../player.h"
#include "../phrase.h"

namespace synth {

class MelodyPlayer : public Player {
public:
	MelodyPlayer(std::ifstream& file);

	inline const Phrase& phrase() const { return phrase_; }
	inline const Audio::NoteList& phrase_notes() const { return phrase_.notes; }
	inline auto pos() { return module_.main_walker().pos(); }

	// fix
	Phrase ParsePhraseAt(uint16_t pos) { return {{}, 0}; }

protected:
	melo::evaluator::Module module_;
	Phrase phrase_;
	const float speed_;

	PLAYER_CALLBACKS_INHERIT
};

} // namespace synth
