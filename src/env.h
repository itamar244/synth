// Environment is the synth's state manager.
// It controls the audio and the melody comparator, also the current octave
#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include "audio.h"
#include "melody_player/melody_comparator.h"
#include "melody_player/melody_player.h"
#include "utils.h"
#include "recorder.h"

namespace synth {

struct State {
	Player* player = nullptr;
	Recorder* recorder = nullptr;
  bool is_song_played = false;

	~State();
};

class Environment {
public:
	~Environment();

	void Tick();

	inline State& state() { return state_; }

	// Audio
	inline Audio* audio() const { return audio_; }
	inline void IncrementOctave() { current_octave_++; }
	inline void DecrementOctave() {
		if (current_octave_ > 0) current_octave_--;
	}

	inline void AddToneWithOctave(uint8_t tone) {
		OnToneWithOctaveCall(tone);
		audio_->AddTone(tone + current_octave_ * 12);
	}

	inline void RemoveToneWithOctave(uint8_t tone) {
		OnToneWithOctaveCall(tone);
		audio_->RemoveTone(tone + current_octave_ * 12);
	}

  void SetAudioType(Audio::AudioType type);

private:
	// the audio manager. the default is `SerialPort`
  Audio* audio_ = new SerialPortAudio();
	State state_;

  int8_t current_octave_ = 4;

	void OnToneWithOctaveCall(uint8_t tone);
};

} // namespace synth
