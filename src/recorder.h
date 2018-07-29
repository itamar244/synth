// Recorder and RecordsPlayer implementation.
// Recorder pushes melodies into memory and RecordsPlayer reads and
// plays melodies by a given index.
// Both classes use the same data format of melodies and read and write
//
// The data format:
// - PHRASE = [LENGTH, SIZE, ...NOTES]
// - MELODY = [...PHRASES, 0]
// - STORE  = [...SONGS]
//
// Each phrase made from length in `milliseconds / 16`, size of notes, and note values.
// Each melody consists from many phrases, ending with zero
#pragma once

#include <cstdint>
#include "phrase.h"
#include "player.h"
#include "timer.h"

namespace synth {

class Recorder : private Timer {
public:
	~Recorder();
	void PushNotes(const Audio::NoteList& notes);

private:
	bool added_notes_ = false;
};

class RecordsPlayer : public Player {
public:
	RecordsPlayer(uint16_t song_pos);

protected:
	PLAYER_CALLBACKS_INHERIT

private:
	uint32_t pos_;
	Phrase cur_phrase_;
};

} // namespace synth
