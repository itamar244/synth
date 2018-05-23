#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <stdint.h>
#include <Arduino.h>
#include "audio.h"
#include "utils.h"
#include "melody_player/parser.h"
#include "melody_player/melody_container.h"
#include "play_wrapper.h"

namespace synth {

class MelodyComparator : public MelodyParser, Player {
public:
	MelodyComparator(const MelodyContainer& container);

	inline float grade() const { return grade_ / max_grade_ * 100; }
	inline bool comparing() const { return comparing_; }
	inline bool ShouldCompare() const { return compare_pos_ < pos(); }

	void AddTonesToCompare(const Audio::ToneList& tones);
	bool NextSection();
	bool Play(Audio* audio);

private:
	MelodyContainer::Sections sections_;
	uint16_t section_time_;
	uint8_t cur_section_;

	uint16_t compare_pos_;
	uint16_t max_grade_;
	float grade_;

	// sahred variables for both playing and comparing phases
  bool started_, ended_, comparing_;

	inline void InitFlags() {
		section_time_ = 0;
		started_ = ended_ = comparing_ = false;
	}

	inline void EatNext() {
		ParseNextPhrase();
		section_time_ += phrase().length;
	}
};

} // namespace synth
