#include "melody_player/melody_player.h"
#include <Arduino.h>
#include "phrase.h"

namespace synth {

void MelodyPlayer::ParsePhrase() {
	MelodyParser::ParsePhrase();
}

const Phrase::Tones& MelodyPlayer::GetPhraseTones() const {
	return phrase_tones();
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	return PassedTime() >= PhraseLengthInMillis(phrase(), speed_);
}

void MelodyPlayer::NextPhrase() {
	MelodyParser::NextPhrase();
}

bool MelodyPlayer::ShouldContinue() const {
	return HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
