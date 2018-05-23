#include "recorder.h"
#include "empty.h"
#include "play_wrapper.h"
#include "store.h"

namespace synth {

namespace {

inline uint32_t MillisScale(uint32_t milliseconds) {
	return milliseconds / 16;
}

uint16_t GetSongStartFromPos(uint8_t song_pos) {
	uint16_t cur_song_pos = 0, pos = 0;

	while (cur_song_pos < song_pos && pos < store::Size() - 1) {
		if (store::Get(pos) == 0) {
			++cur_song_pos;
			++pos;
		} else {
			// adding phrase's tones size and
			// the bytes representings amount of tones and length
			pos += store::Get(pos + 1) + 2;
		}
	}

	return pos;
}

} // namespace

Recorder::~Recorder() {
	// terminate the song record
	store::Push(0);
}

void Recorder::PushTones(const Audio::ToneList& tones) {
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

bool RecordsPlayer::Play(Audio* audio) {
	return PlayWrapper(
			audio,
			this,
			// eat_next
			[this]() {
				uint8_t tones_size = store::Get(pos_ + 1);
				Phrase::Tones tones(tones_size);

				for (uint16_t i = 0; i < tones_size; i++) {
					tones[i] = store::Get(pos_ + i + 2);
				}

				cur_phrase_ = {tones, store::Get(pos_)};
			},
			// get_phrase_tones
			[this]() { return cur_phrase_.tones; },
			// should_change_to_next_phrase
			[this]() {
				return MillisScale(millis() - prev_millis_) >= cur_phrase_.length;
			},
			// next_phrase
			[this]() { pos_ += cur_phrase_.tones.size() + 2; },
			// is_finished
			[this]() { return pos_ == store::Size() || store::Get(pos_) == 0; },
			// when_finished
			empty::callback);
}

} // namespace synth
