#include "sound.h"
#include <cmath>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <map>
#include <utility>
#include <SFML/Audio.hpp>
#include "audio.h"
#include <atic/iterables.h>

namespace synth::sound {

namespace {

inline float BaseOctaveNoteToFrequency(Audio::Note note) {
	switch (note) {
		case 0: return 16.35; // C
		case 1: return 17.32; // C#
		case 2: return 18.35; // D
		case 3: return 19.45; // D#
		case 4: return 20.60; // E
		case 5: return 21.83; // F
		case 6: return 23.12; // F#
		case 7: return 24.50; // G
		case 8: return 25.96; // G#
		case 9: return 27.50; // A
		case 10: return 29.14; // A#
		case 11: return 30.87; // B
		default: return 0;
	}
}

inline float NoteToFrequency(Audio::Note note) {
	return BaseOctaveNoteToFrequency(note % 12) * std::pow(2, note / 12);
}

class SoundWave {
public:
	SoundWave(sf::SoundBuffer* buffer, sf::Sound* sound)
			: buffer_(buffer), sound_(sound) {}

	~SoundWave() {
		delete buffer_;
		delete sound_;
	}

	inline void SetBuffer(sf::SoundBuffer* next_buffer) {
		sound_->setBuffer(*next_buffer);
		delete buffer_;
		buffer_ = next_buffer;
	}

	inline void RestartSound() {
		sound_->setPlayingOffset(sf::milliseconds(0));
	}

	inline void Play() { sound_->play(); }

private:
	sf::SoundBuffer* buffer_;
	sf::Sound* sound_;
};

constexpr uint16_t WAVE_PRECISION = 100;
constexpr double k2Pi = M_PI * 2;

inline int16_t* GetWave(uint8_t amount_of_notes) {
	static int16_t raw_wave[WAVE_PRECISION];

	uint16_t amplitude = (4 - std::log(amount_of_notes + M_E)) * 1e4;
	for (uint16_t i = 0; i < WAVE_PRECISION; i++) {
		raw_wave[i] = amplitude * std::sin(k2Pi * (float(i) / WAVE_PRECISION));
	}

	return raw_wave;
}

inline sf::SoundBuffer* WaveToBuffer(int16_t* raw_wave, float frequency) {
	auto buffer = new sf::SoundBuffer();
	buffer->loadFromSamples(
			raw_wave, WAVE_PRECISION, 1, WAVE_PRECISION * frequency);
	return buffer;
}

SoundWave* PlaySineWave(Audio::Note note, int16_t* raw_wave, float frequency) {
	auto buffer = WaveToBuffer(raw_wave, frequency);

	auto sound = new sf::Sound(*buffer);
	sound->setLoop(true);
	return new SoundWave(buffer, sound);
}

} // namespace


void SetPlayedNotes(const Audio::NoteList& notes) {
	static std::map<Audio::Note, SoundWave*> waves;

	int16_t* raw_wave = GetWave(notes.size());

	for (auto pair : waves) {
		if (!atic::HasItem(notes, pair.first)) {
			delete pair.second;
			waves.erase(pair.first);
		} else {
			pair.second->SetBuffer(
					WaveToBuffer(raw_wave, NoteToFrequency(pair.first)));
		}
	}

	for (auto note : notes) {
		auto it = waves.find(note);
		if (it == waves.end()) {
			waves[note] = PlaySineWave(note, raw_wave, NoteToFrequency(note));
		} else {
			it->second->RestartSound();
		}
	}

	for (auto pair : waves) {
		pair.second->Play();
	}

	std::cout << waves.size() << '\n';
}

} // namespace synth::sound
