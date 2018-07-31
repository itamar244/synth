// MelodyComparator's roles are:
//   - play the sections of a melody.
//   - compare a given phrases to the melody.
//   - calculate a grade that represents the given phrases simillarity to the melody.
#pragma once

#include <cstdint>
#include "melody_container.h"
#include "pgm_array.h"
#include "melody_player.h"

namespace synth {

class MelodyComparator : public MelodyPlayer {
public:
	MelodyComparator(const MelodyContainer& container);

	inline float grade() const {
		return grade_ / max_grade_ * 100.0;
	}

	void AddNotesToCompare(const Audio::NoteList& notes);
	bool NextSection();
	MelodyComparator* ToComparator() override { return this; }

protected:
	void ParsePhrase() override;
	bool ShouldContinue() const override;
	void WhenFinished() override;

private:
	const PGMArray sections_;
	uint16_t section_time_;
	uint8_t cur_section_;

	uint16_t compare_pos_;
	float grade_, speed_, max_grade_;

	inline void InitFlags() {
		section_time_ = 0;
		ended_ = started_ = false;
	}
};

} // namespace synth
