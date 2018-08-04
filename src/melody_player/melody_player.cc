#include "melody_player.h"
#include "../melo/melo.h"
#include <boost/filesystem/fstream.hpp>
#include "../audio.h"

namespace synth {

MelodyPlayer::MelodyPlayer(std::ifstream& file)
		:	module_(melo::CreateModule(file))
		, speed_(module_.Get("speed")->AsNumberValue()->value) {}

void MelodyPlayer::ParsePhrase() {
	auto melo_phrase = module_.main_walker().GetCurPhrase();
	phrase_ = {melo_phrase.notes, melo_phrase.length};
}

const Audio::NoteList& MelodyPlayer::GetPhraseNotes() const {
	return phrase_notes();
}

bool MelodyPlayer::ShouldChangeToNextPhrase() const {
	return PassedTime() >= PhraseLengthInMillis(phrase(), speed_);
}

void MelodyPlayer::NextPhrase() {
	module_.main_walker().Next();
}

bool MelodyPlayer::ShouldContinue() const {
	return module_.main_walker().HasNextPhrase();
}

void MelodyPlayer::WhenFinished() {}

} // namespace synth
