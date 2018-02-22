#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include <Arduino.h>
#include "audio.h"
#include "utils.h"
#include "song_player/pgm_song_parser.h"
#include "song_player/song_container.h"

namespace synth {

class MelodyComparator: public PGMSongParser {
public:
	MelodyComparator(const SongContainer& container);

	inline float grade() const { return grade_ / max_grade_ * 100; }
	inline bool comparing() const { return comparing_; }
	inline bool ShouldCompare() const { return compare_pos_ < pos(); }

	void AddTonesToCompare(const Audio::ToneList& tones);
	bool NextSection();
	bool Play(Audio* audio);

private:
	SongContainer::Sections sections_;
	uint16_t section_time_;
	uint8_t cur_section_;

	uint16_t compare_pos_;
	uint16_t max_grade_;
	float grade_;

	// sahred variables for both playing and comparing phases
  bool started_section_;
	bool ended_section_;
	bool comparing_;
	uint32_t prev_millis_;

	inline void InitFlags() {
		section_time_ = 0;
		started_section_ = ended_section_ = comparing_ = false;
	}

	inline void PlayNext(Audio* audio) {
		ParseNextPhrase();
    audio->AddTones(phrase().tones);
		section_time_ += phrase().length;
		prev_millis_ = millis();
	}
};

} // namespace synth
