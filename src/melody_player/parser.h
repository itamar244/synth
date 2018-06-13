#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "audio.h"
#include "melody_player/melody_container.h"
#include "melody_player/pgm_array.h"
#include "phrase.h"

namespace synth {

class MelodyParser {
public:
  MelodyParser(const MelodyContainer& container);

	inline bool HasNextPhrase() const {
		return pos_ < melody_.size();
	}
	inline const Audio::ToneList& phrase_tones() const {
		return phrase_.tones;
	}

protected:
	inline const Phrase& phrase() const { return phrase_; }
	inline const uint16_t pos() const { return pos_; }

  void ParsePhrase();
  void NextPhrase();
  Phrase ParsePhraseAt(uint16_t pos);

private:
  const PGMArray melody_;
  Phrase phrase_;
  uint16_t pos_;
};

} // namespace synth
