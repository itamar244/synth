#include "sound.h"
#include <cmath>
#include <cstdint>
#include <chrono>
#include <map>
#include <thread>
#include <SFML/Audio.hpp>
#include "./audio.h"
#include "./utils.h"

namespace synth::sound {

namespace {

float NoteToFrequency(Audio::Note note) {
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

constexpr uint16_t WAVE_PRECISION = 100;
constexpr double TWO_PI = 6.28318;

int16_t* GetWave(uint8_t amount_of_notes) {
	static uint8_t last_amount = 0;
	static int16_t raw_wave[WAVE_PRECISION];

	if (last_amount != amount_of_notes) {
		last_amount = amount_of_notes;
		uint16_t amplitude = (4 - amount_of_notes) * 1e4;
		for (uint16_t i = 0; i < WAVE_PRECISION; i++) {
			raw_wave[i] = amplitude * std::sin(TWO_PI * (float(i) / WAVE_PRECISION));
		}
	}

	return raw_wave;
}

void PlaySineWave(Audio::Note note, uint8_t amount_of_notes) {
	float frequency = NoteToFrequency(note % 12) * std::pow(2, note / 12);
	sf::SoundBuffer buffer;
	buffer.loadFromSamples(
		GetWave(amount_of_notes), WAVE_PRECISION, 1, WAVE_PRECISION * frequency);

	sf::Sound sound(buffer);
	sound.setLoop(true);
	sound.play();
	for (;;) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

} // namespace


void SetPlayedNotes(const Audio::NoteList& notes) {
	static std::map<Audio::Note, std::thread> sounds;

	sounds.clear();

	for (auto note : notes) {
		sounds[note] = std::thread(PlaySineWave, note, notes.size());
	}
}

} // namespace synth::sound
