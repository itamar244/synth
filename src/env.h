// Environment is the synth's state manager.
// It controls the audio and the melody comparator, also the current octave
#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include <utility.h>
#include "audio.h"
#include "melody_player/melody_comparator.h"
#include "melody_player/melody_player.h"
#include "melody_player/melodies.h"
#include "utils.h"
#include "recorder.h"

namespace synth {

class Environment {
public:
	~Environment();

	void Tick();

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

	inline void SetPlayer(Player* player) {
		utils::SetPtr(player_, player);
	}
	template<class PlayerType>
	inline void SetPlayer(const char* melody_name) {
		SetPlayer(new PlayerType(melodies::GetContainer(melody_name)));
	}

	inline void StartPlaying() { is_song_played_ = true; }

	inline void StartRecording() { utils::SetPtr(recorder_, new Recorder()); }
	inline void StopRecording() {	utils::MaybeDeletePtr(recorder_); }

	void DeletePlayer();
	// the pair holds two values, first - if the there is next section,
	// second - if there isn't another section than the comparator's grade
	std::pair<bool, float> ComparatorNextSection();
  void SetAudioType(Audio::AudioType type);

private:
	// the audio manager. the default is `SerialPort`
  Audio* audio_ = new SerialPortAudio();
	Player* player_ = nullptr;
	Recorder* recorder_ = nullptr;
  bool is_song_played_ = false;

  int8_t current_octave_ = 4;

	void OnToneWithOctaveCall(uint8_t tone);
};

} // namespace synth
