// Environment is the synth's state manager.
// It controls the audio and the melody comparator, also the current octave
#pragma once

#include <fstream>
#include <memory>
#include <utility>
#include <string>
#include "audio.h"
#include "melody_player/melody_player.h"
#include "player.h"
#include <atic/ptr.h>
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

	inline void AddNoteWithOctave(Audio::Note note) {
		OnNoteWithOctaveCall(note);
		audio_->AddNote(note + current_octave_ * 12);
	}
	inline void RemoveNoteWithOctave(Audio::Note note) {
		OnNoteWithOctaveCall(note);
		audio_->RemoveNote(note + current_octave_ * 12);
	}

	inline void SetPlayer(Player* player) {
		atic::SetPtr(player_, player);
	}
	template<class PlayerType>
	inline void SetPlayer(const std::string& path) {
		std::ifstream file(path);
		SetPlayer(new PlayerType(file));
	}

	inline void StartPlaying() { is_song_played_ = true; }

	inline void StartRecording() {
		recorder_ = std::make_unique<Recorder>();
		// SetLedBulbColor(255, 0, 0);
	}
	inline void StopRecording() {
		recorder_ = nullptr;
		// ClearLedBulb();
	}
	//
	void DeletePlayer();
	std::pair<
			bool /* has_next_section */,
			float /* grade */>
			ComparatorNextSection();
  void SetAudioType(Audio::AudioType type);

private:
  Audio* audio_ = new BuiltinAudio();
	Player* player_ = nullptr;
	std::unique_ptr<Recorder> recorder_ = nullptr;
  bool is_song_played_ = false;

  int8_t current_octave_ = 4;

	void OnNoteWithOctaveCall(Audio::Note note);
};

} // namespace synth
