#include "recorder.h"
#include "eeprom.h"

namespace synth {

namespace {

inline uint8_t MillisScale(uint32_t milliseconds) {
	return milliseconds / 16 % 255;
}

uint16_t GetSongStartFromPos(uint8_t song_pos) {
	uint16_t cur_song_pos = 0, pos = 0;

	while (song_pos > cur_song_pos) {
		// adding phrase's tones size and
		// the bytes representings amount of tones and length
		pos += eeprom::Get(pos) + 2;
		if (eeprom::Get(pos) == 0) {
			++cur_song_pos;
		}
		++pos;
	}

	return pos;
}

inline Phrase GetPhraseFromEEPROM(uint16_t pos) {
	uint32_t tones_length = eeprom::Get(pos);
	Phrase::Tones tones;
	tones.reserve(tones_length);

	for (uint16_t i = 0; i < tones_length; i++) {
		tones.push_back(eeprom::Get(pos + i + 1));
	}

	return {tones, eeprom::Get(pos + tones_length + 1)};
}

} // namespace

void Recorder::PushTones(const Audio::ToneList& tones) {
	eeprom::Push(tones.size());

	uint32_t cur_millis = millis();

	for (auto& tone : tones) {
		eeprom::Push(tone);
	}

	eeprom::Push(MillisScale(cur_millis - prev_millis_));
	prev_millis_ = cur_millis;
}

RecordsPlayer::RecordsPlayer(uint16_t song_pos)
	: pos_(GetSongStartFromPos(song_pos))
	, prev_millis_(millis())
	, inited_(false)
	, cur_phrase_(GetPhraseFromEEPROM(pos_)) {}

bool RecordsPlayer::Tick(Audio* audio) {
	if (!inited_) {
		inited_ = true;
		audio->AddTones(cur_phrase_.tones);
		return true;
	}

	uint32_t cur_millis = millis();

	if (MillisScale(cur_millis - prev_millis_) >= cur_phrase_.length) {
		audio->RemoveTones(cur_phrase_.tones);
		pos_ += cur_phrase_.length + 2;

		// checking if song ended
		if (pos_ == eeprom::Size() || eeprom::Get(pos_) == 0) {
			return false;
		}
		cur_phrase_ = GetPhraseFromEEPROM(pos_);
		audio->AddTones(cur_phrase_.tones);
	}

	return true;
}

} // namespace synth
