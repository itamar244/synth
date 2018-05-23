#pragma once

#include <stdint.h>
#include "melody_player/parser.h"
#include "melody_player/melody_container.h"
#include "player.h"

namespace synth {

class MelodyComparator : public Player, public MelodyParser {
public:
	MelodyComparator(const MelodyContainer& container);

	inline float grade() const { return grade_ / max_grade_ * 100; }
	inline bool comparing() const { return comparing_; }
	inline bool ShouldCompare() const { return compare_pos_ < pos(); }

	void AddTonesToCompare(const Audio::ToneList& tones);
	bool NextSection();
protected:
	PLAYER_CALLBACKS_INHERIT

private:
	MelodyContainer::Sections sections_;
	uint16_t section_time_;
	uint8_t cur_section_;

	uint16_t compare_pos_;
	uint16_t max_grade_;
	float grade_;

  bool comparing_;

	inline void InitFlags() {
		section_time_ = 0;
		started_ = comparing_ = false;
	}
};

} // namespace synth
