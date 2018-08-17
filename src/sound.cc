#include "sound.h"
#include <cmath>
#include <cstdint>
#include <map>
#include <memory>
#include <SFML/Audio.hpp>
#include <atic/iterables.h>
#include "types.h"

namespace synth {

namespace {

inline float BaseOctaveNoteToFrequency(types::Note note) {
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

inline float NoteToFrequency(types::Note note) {
	return BaseOctaveNoteToFrequency(note % 12) * std::pow(2, note / 12);
}

constexpr uint16_t WAVE_PRECISION = 100;
constexpr double k2PI = M_PI * 2;

inline int16_t* GetWave(uint8_t amount_of_notes) {
	static int16_t raw_wave[WAVE_PRECISION];

	uint16_t amplitude = (4 - std::log(amount_of_notes + M_E)) * 1e4;
	for (uint16_t i = 0; i < WAVE_PRECISION; i++) {
		raw_wave[i] = amplitude * std::sin(k2PI * (float(i) / WAVE_PRECISION));
	}

	return raw_wave;
}

inline sf::SoundBuffer WaveToBuffer(int16_t* raw_wave, float frequency) {
	sf::SoundBuffer buffer;
	buffer.loadFromSamples(
			raw_wave, WAVE_PRECISION, 1, WAVE_PRECISION * frequency);
	return buffer;
}

} // namespace

SoundWave::SoundWave(types::Note note, int16_t* raw_wave, float frequency)
 		: buffer_(WaveToBuffer(raw_wave, frequency)), sound_(buffer_) {
	sound_.setLoop(true);
}

void SineWavesSynth::SetPlayedNotes(const types::NoteList& notes) {
	int16_t* raw_wave = GetWave(notes.size());

	for (auto& pair : waves_) {
		if (!atic::HasItem(notes, pair.first)) {
			waves_.erase(pair.first);
		} else {
			pair.second->SetBuffer(
					WaveToBuffer(raw_wave, NoteToFrequency(pair.first)));
		}
	}

	for (auto note : notes) {
		auto it = waves_.find(note);
		if (it == waves_.end()) {
			waves_.insert({
				note,
				std::make_unique<SoundWave>(note, raw_wave, NoteToFrequency(note)),
			});
		} else {
			it->second->RestartSound();
		}
	}

	for (auto& pair : waves_) {
		pair.second->Play();
	}
}

} // namespace synth
