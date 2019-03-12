#include "recorder.h"
#include <utility>
#include <iostream>
#include <atic/ptr.h>
#include "store.h"

namespace synth {

namespace {

inline uint32_t MillisScale(uint32_t milliseconds) {
	return milliseconds;
}

uint16_t GetSongStartFromPos(uint8_t song_pos) {
	uint16_t cur_song_pos = 0, pos = 0;

	auto it2 = store::GetIterateor();
	for (; it2; ++it2) {
		std::cout << *it2 << ", ";
	}
	std::cout << '\n';

	auto it = store::GetIterateor();

	std::cout << (int)song_pos << '\n';

	while (cur_song_pos < song_pos && it) {
		std::cout << cur_song_pos << '\n';
		std::cout << store::Get(pos) << ": " << store::Get(pos + 1) << '\n';
		std::cout << bool(it) << '\n';

		if (store::Get(pos) == 0 && store::Get(pos + 1) == 0) {
			++cur_song_pos;
			pos += 2;
		} else {
			// adding phrase's notes size and
			// the bytes representings amount of notes and length
			pos += store::Get(pos + 1) + 2;
		}
	}

	std::cout << pos << '\n';
	return pos;
}

} // namespace

Recorder::~Recorder() {
	// terminate the song record
	if (added_notes_) {
		store::Push(0, 0);
	}
}

void Recorder::PushNotes(const Audio::NoteList& notes) {
	uint32_t passed_time = MillisScale(GetUpdateTime());

	if (passed_time == 0) {
		return;
	}

	if (!added_notes_) added_notes_ = true;

	store::Push(notes.size());

	for (auto& note : notes) {
		store::Push(note);
	}

	store::Push(passed_time);
}

RecordsPlayer::RecordsPlayer(uint16_t song_pos)
		: pos_(GetSongStartFromPos(song_pos)) {}

void RecordsPlayer::ParsePhrase() {
	uint8_t notes_size = store::Get(pos_ + 1);
	Audio::NoteList notes;

	for (uint16_t i = 0; i < notes_size; i++) {
		notes.push_back(store::Get(pos_ + i + 2));
	}

	cur_phrase_ =	{
		std::move(notes),
		store::Get(pos_),
	};
}

const Audio::NoteList& RecordsPlayer::GetPhraseNotes() const {
	return cur_phrase_.notes;
}

bool RecordsPlayer::ShouldChangeToNextPhrase() const {
	return MillisScale(PassedTime()) >= cur_phrase_.length;
}

void RecordsPlayer::NextPhrase() {
	pos_ += cur_phrase_.notes.size() + 2;
}

bool RecordsPlayer::ShouldContinue() const {
	return pos_ < store::Size() - 1
			&& (store::Get(pos_) != 0 || store::Get(pos_ + 1) != 0);
}

void RecordsPlayer::WhenFinished() {}

} // namespace synth
