#include "melody_player/melody_player.h"
#include <Arduino.h>
#include "phrase.h"

namespace synth {

void MelodyPlayer::EatNext() {
	ParseNextPhrase();
}

const Phrase::Tones& MelodyPlayer::GetPhraseTones() const {
	return phrase_tones();
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	return millis() - prev_millis_ >= PhraseLengthInMillis(phrase(), speed_);
}

void MelodyPlayer::NextPhrase() {}

bool MelodyPlayer::ShouldContinue() const {
	return HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
