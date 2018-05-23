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

#define V(FUNC)                                                                \
	inline void FUNC ## ToneWithOctave(uint8_t tone) {                           \
		if (MelodyComparator* comparator = state_.player->ToComparator()) {        \
			comparator->AddTonesToCompare(audio_->current_tones());                  \
		}                                                                          \
		if (state_.recorder != nullptr) {                                          \
		  state_.recorder->PushTones(audio_->current_tones());                     \
		}                                                                          \
		audio_->FUNC ## Tone(tone + current_octave_ * 12);                         \
	}
	V(Add) V(Remove)
#undef V

  void SetAudioType(Audio::AudioType type);

private:
	// the audio manager. the default is `SerialPort`
  Audio* audio_ = new SerialPortAudio();
	State state_;

  int8_t current_octave_ = 4;
};

} // namespace synth
