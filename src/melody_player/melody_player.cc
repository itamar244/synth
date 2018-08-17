#include "melody_player/melody_player.h"
#include <boost/filesystem/fstream.hpp>
#include <melo/melo.h>
#include "audio.h"

namespace synth {

MelodyPlayer::MelodyPlayer(std::ifstream& file)
		:	module_(melo::CreateModule(file))
		, walker_(module_.GetMain())
		, speed_(module_.GetExport("speed")->ExpectNumberValue()->value) {}

MelodyPlayer::~MelodyPlayer() {}

void MelodyPlayer::ParsePhrase() {
	auto melo_phrase = walker_.GetCurPhrase();
	phrase_ = {melo_phrase.notes, melo_phrase.length};
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
