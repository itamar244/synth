// Recorder and RecordsPlayer implementation.
// Recorder pushes melodies into memory and RecordsPlayer reads and
// plays melodies by a given index.
// Both classes use the same data format of melodies and read and write
// the melodies from the store.
//
// The data format:
// - PHRASE = [LENGTH, SIZE, ...TONES]
// - MELODY = [...PHRASES, 0]
// - STORE  = [...SONGS]
//
// Each phrase made from length in `milliseconds / 16`, size of tones, and tone values.
// Each melody consists from many phrases, ending with zero
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "audio.h"
#include "phrase.h"
#include "store.h"

namespace synth {

class Recorder {
public:
	~Recorder();
	void PushTones(const Audio::ToneList& tones);

private:
	uint32_t prev_millis_ = millis();
};

class RecordsPlayer {
public:
	RecordsPlayer(uint16_t song_pos);
	bool Play(Audio* audio);


private:
	bool started_ = false;
	uint32_t pos_, prev_millis_ = millis();
	Phrase cur_phrase_;

	bool Finished() const {
		return pos_ == store::Size() || store::Get(pos_) == 0;
	}

	void ReadCurrentPhrase();
};

} // namespace synth

