#include "melody_player/melody_player.h"
#include <utility>

namespace synth {

MelodyPlayer::MelodyPlayer(std::ifstream& file)
		:	module_(melo::CreateModule(file))
		, walker_(module_.GetMain())
		, speed_(module_.GetExport("speed")->ExpectNumberValue()->value) {}

void MelodyPlayer::ParsePhrase() {
	phrase_ = std::move(walker_.GetCurPhrase());
}

const Audio::NoteList& MelodyPlayer::GetPhraseNotes() const {
	return phrase_.notes;
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	return PassedTime() >= phrase_length();
}

void MelodyPlayer::NextPhrase() {
	walker_.Next();
}

bool MelodyPlayer::ShouldContinue() const {
	return walker_.HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
