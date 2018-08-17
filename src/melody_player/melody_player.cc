#include "melody_player/melody_player.h"
#include <boost/filesystem/fstream.hpp>
#include "audio.h"

namespace synth {

MelodyPlayer::MelodyPlayer(std::ifstream& file)
		:	module_(melo::CreateModule(file))
		, walker_(module_.GetMain())
		, speed_(module_.GetExport("speed")->ExpectNumberValue()->value) {}

MelodyPlayer::~MelodyPlayer() {}

void MelodyPlayer::ParsePhrase() {
	phrase_ = walker_.GetCurPhrase();
}

const Audio::NoteList& MelodyPlayer::GetPhraseNotes() const {
	return phrase_notes();
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	return PassedTime() >= PhraseLengthInMillis(phrase(), speed_);
}

void MelodyPlayer::NextPhrase() {
	walker_.Next();
}

bool MelodyPlayer::ShouldContinue() const {
	return walker_.HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
