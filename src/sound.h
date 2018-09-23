#pragma once

#include "types.h"
#include <map>
#include <memory>
#include <SFML/Audio.hpp>

namespace synth {

class SoundWave {
public:
	SoundWave(types::Note note, int16_t* raw_wave, float frequency);

	inline void SetBuffer(const sf::SoundBuffer& next_buffer) {
		sound_.resetBuffer();
		buffer_ = next_buffer;
		sound_.setBuffer(buffer_);
	}

	inline void RestartSound() {
		sound_.setPlayingOffset(sf::milliseconds(0));
	}

	inline void Play() { sound_.play(); }

private:
	sf::SoundBuffer buffer_;
	sf::Sound sound_;
};

class SineWavesSynth {
public:
	void SetPlayedNotes(const types::NoteList& notes);

private:
	std::map<types::Note, std::unique_ptr<SoundWave>> waves_;
};

} // namespace synth
