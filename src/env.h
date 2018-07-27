// Environment is the synth's state manager.
// It controls the audio and the melody comparator, also the current octave
#pragma once

// #include "audio.h"
// #include "led_bulb.h"
// #include "melody_player/melody_comparator.h"
// #include "melody_player/melody_player.h"
// #include "melody_player/melodies.h"
// #include "utils.h"
// #include "recorder.h"

namespace synth {

class Environment {
public:
	~Environment();

	void Tick();

	// Audio
	// inline Audio* audio() const { return audio_; }
	// inline void IncrementOctave() { current_octave_++; }
	// inline void DecrementOctave() {
	// 	if (current_octave_ > 0) current_octave_--;
	// }
	//
	// inline void AddNoteWithOctave(Audio::Note note) {
	// 	OnNoteWithOctaveCall(note);
	// 	audio_->AddNote(note + current_octave_ * 12);
	// }
	// inline void RemoveNoteWithOctave(Audio::Note note) {
	// 	OnNoteWithOctaveCall(note);
	// 	audio_->RemoveNote(note + current_octave_ * 12);
	// }
	//
	// inline void SetPlayer(Player* player) {
	// 	utils::SetPtr(player_, player);
	// }
	// template<class PlayerType>
	// inline void SetPlayer(const char* melody_name) {
	// 	SetPlayer(new PlayerType(melodies::GetContainer(melody_name)));
	// }
	//
	// inline void StartPlaying() { is_song_played_ = true; }
	//
	// inline void StartRecording() {
	// 	utils::SetPtr(recorder_, new Recorder());
	// 	SetLedBulbColor(255, 0, 0);
	// }
	// inline void StopRecording() {
	// 	utils::MaybeDeletePtr(recorder_);
	// 	ClearLedBulb();
	// }
	//
	// void DeletePlayer();
	// std::pair<
	// 		bool /* has_next_section */,
	// 		float /* grade */>
	// 		ComparatorNextSection();
  // void SetAudioType(Audio::AudioType type);

private:
  // Audio* audio_ = new SerialPortAudio();
	// Player* player_ = nullptr;
	// Recorder* recorder_ = nullptr;
  // bool is_song_played_ = false;

  // int8_t current_octave_ = 4;

	// void OnNoteWithOctaveCall(Audio::Note note);
};

} // namespace synth
