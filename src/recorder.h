#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "audio.h"
#include "phrase.h"

namespace synth {

class Recorder {
public:
	void PushTones(const Audio::ToneList& tones);

private:
	uint32_t prev_millis_ = millis();
};

class RecordsPlayer {
public:
	RecordsPlayer(uint16_t song_pos);
	bool Tick(Audio* audio);

private:
	uint32_t pos_, prev_millis_ = millis();
	bool inited_;
	Phrase cur_phrase_;
};

} // namespace synth

