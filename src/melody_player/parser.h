#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "melody_player/melody_container.h"
#include "phrase.h"

namespace synth {

class MelodyParser {
public:
  typedef const uint8_t* Melody;

  MelodyParser(const MelodyContainer& container);

	inline bool HasNextPhrase() const {
		return pos_ < size_;
	}
	inline const std::vector<uint8_t>& phrase_tones() const {
		return phrase_.tones;
	}

protected:
	inline const Phrase& phrase() const { return phrase_; }
	inline const uint16_t pos() const { return pos_; }

  void ParsePhrase();
  void NextPhrase();
  Phrase ParsePhraseAt(uint16_t pos);

private:
  const Melody melody_;
  const uint16_t size_;
  Phrase phrase_;
  uint16_t pos_;
};

} // namespace synth
