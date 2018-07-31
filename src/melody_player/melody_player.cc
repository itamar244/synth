#include "melody_player.h"
#include "../audio.h"

namespace synth {

void MelodyPlayer::ParsePhrase() {
	MelodyParser::ParsePhrase();
}

const Audio::NoteList& MelodyPlayer::GetPhraseNotes() const {
	return phrase_notes();
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
