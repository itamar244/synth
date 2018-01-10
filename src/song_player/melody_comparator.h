#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include "song_player/song_player.h"

namespace synth {

class MelodyComparator: public SongPlayer {
public:
	inline float grade() const { return grade_; }
	inline bool ShouldCompare() const { return pos_ >= compare_pos_; }

	void Init(Song song, uint16_t size);
	void AddPhraseToCompare(const PGMPhrase& phrase);

private:
	uint16_t compare_pos_;
	uint16_t phrase_count_;
	float grade_;
};

} // namespace synth
