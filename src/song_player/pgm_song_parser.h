#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "song_player/song_container.h"

namespace synth {

class PGMSongParser {
public:
  typedef const uint8_t* Song;
	struct PGMPhrase {
		std::vector<uint8_t> tones;
  	uint8_t length;
	};

  PGMSongParser(const SongContainer& container);

	inline bool HasNextPhrase() const {
		return pos_ < size_;
	}
	inline const std::vector<uint8_t>& phrase_tones() const {
		return phrase_.tones;
	}

protected:
  Song song_;
  PGMPhrase phrase_;
  uint16_t size_;
  uint16_t pos_;

  void ParseNextPhrase();
  PGMPhrase ParsePhraseAt(uint16_t pos);
};

} // namespace synth
