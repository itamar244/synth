// MelodyComparator's roles are:
//   - play the sections of a melody.
//   - compare a given phrases to the melody.
//   - calculate a grade that represents the given phrases simillarity to the melody.
#pragma once

#include <fstream>
#include <melo/melo.h>
#include <melo/phrase.h>
#include "player.h"
#include "melody_player/melody_player.h"

namespace synth {

class MelodyComparator : public MelodyPlayer {
public:
	MelodyComparator(std::ifstream& file);

	inline float grade() const {
		return grade_ / max_grade_ * 100.0;
	}

	void AddNotesToCompare(const Audio::NoteList& notes);
	bool NextSection();

protected:
	bool ShouldContinue() const override;
	void WhenFinished() override;

private:
	float grade_, max_grade_;
	bool ended_, started_;
	unsigned cur_section_ = 0;

	inline void InitFlags() {
		ended_ = started_ = false;
	}
};

} // namespace synth
