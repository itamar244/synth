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
	inline bool ShouldCompare() const { return compare_pos_ < pos_; }

	void AddTonesToCompare(const Audio::ToneList& tones);
	bool NextSection();
	bool Play(Audio* audio);

private:
	const std::vector<uint8_t>& sections_;
	uint16_t section_time_;
	uint8_t cur_section_;

	uint16_t compare_pos_;
	uint16_t max_grade_;
	float grade_;

  bool started_section_;
	bool ended_section_;
	bool comparing_;
	// used both play phase and compare phase for async time counting
	uint32_t prev_millis_;

	inline void InitFlags(bool value) {
		started_section_ = ended_section_ = comparing_ = value;
	}

	inline void PlayNext(Audio* audio) {
		ParseNextPhrase();
    audio->AddTones(phrase_.tones);
		section_time_ += phrase_.length;
		prev_millis_ = millis();
	}
};

} // namespace synth
