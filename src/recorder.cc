#include "recorder.h"
#include "store.h"

namespace synth {

namespace {

inline uint8_t StoreGetPhraseLength(uint16_t pos) {
	return store::Get(pos + 1);
}

inline uint32_t MillisScale(uint32_t milliseconds) {
	return milliseconds / 16;
}

uint16_t GetSongStartFromPos(uint8_t song_pos) {
	uint16_t cur_song_pos = 0, pos = 0;

	while (cur_song_pos < song_pos && pos < store::Size() - 2) {
		if (store::Get(pos) == 0 && store::Get(pos + 1) == 0) {
			++cur_song_pos;
			pos += 2;
		} else {
			// adding phrase's tones size and
			// the bytes representings amount of tones and length
			pos += StoreGetPhraseLength(pos) + 2;
		}
	}

	return pos;
}

} // namespace

Recorder::~Recorder() {
	// terminate the song record
	if (added_notes_) {
		store::Push(0, 0);
	}
}

void Recorder::PushTones(const Audio::ToneList& tones) {
	if (!added_notes_) added_notes_ = true;
	uint32_t cur_millis = millis();

	store::Push(MillisScale(cur_millis - prev_millis_));
	store::Push(tones.size());

	for (auto& tone : tones) {
		store::Push(tone);
	}


	prev_millis_ = cur_millis;
}

RecordsPlayer::RecordsPlayer(uint16_t song_pos)
		: pos_(GetSongStartFromPos(song_pos)) {}

void RecordsPlayer::ParsePhrase() {
	uint8_t tones_size = StoreGetPhraseLength(pos_);
	Phrase::Tones tones(tones_size);

	for (uint16_t i = 0; i < tones_size; i++) {
		tones[i] = store::Get(pos_ + i + 2);
	}

	cur_phrase_ = {tones, store::Get(pos_)};
}

const Phrase::Tones& RecordsPlayer::GetPhraseTones() const {
	return cur_phrase_.tones;
}

bool RecordsPlayer::ShouldChangeToNextPhrase() const {
	return MillisScale(millis() - prev_millis_) >= cur_phrase_.length;
}

void RecordsPlayer::NextPhrase() {
	pos_ += cur_phrase_.tones.size() + 2;
}

bool RecordsPlayer::ShouldContinue() const {
	return pos_ < store::Size() - 1
			&& (store::Get(pos_) != 0 || store::Get(pos_ + 1) != 0);
}

void RecordsPlayer::WhenFinished() {}

} // namespace synth
