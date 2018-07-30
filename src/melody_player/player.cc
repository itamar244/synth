#include "./player.h"
#include <iostream>
#include "../audio.h"

namespace synth {

void MelodyPlayer::ParsePhrase() {
	MelodyParser::ParsePhrase();
}

const Audio::NoteList& MelodyPlayer::GetPhraseNotes() const {
	return phrase_notes();
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	bool change = PassedTime() >= PhraseLengthInMillis(phrase(), 1);
	return change;
}

void MelodyPlayer::NextPhrase() {
	MelodyParser::NextPhrase();
}

bool MelodyPlayer::ShouldContinue() const {
	return HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
