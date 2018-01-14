#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include "audio.h"
#include "song_player/melody_comparator.h"
#include "song_player/song_container.h"
#include "song_player/songs.h"

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

#define V(FUNC)                                                                \
	inline void FUNC ## ToneWithOctave(uint8_t tone) {                           \
		if (comparator_ != nullptr && comparator_->comparing()) {                  \
			comparator_->AddTonesToCompare(audio_->current_tones());                 \
		}                                                                          \
		audio_->FUNC ## Tone(tone + current_octave_ * 12);                         \
	}
	V(Add) V(Remove)
#undef V

  void SetAudioType(Audio::Type type);

  // Song
	inline void PlaySong() { is_song_played_ = true; }
	inline void PauseSong() { is_song_played_ = false; }
  inline void SetCurrentSong(
			const uint8_t* song,
			uint16_t size,
			const std::vector<uint8_t>& sections) {
		if (cur_song_ != nullptr) delete cur_song_;
		cur_song_ = new SongContainer{song, size, sections};
  }
	inline const SongContainer* cur_song() const {
		return cur_song_;
	}
	inline void SetMelodyComparator(MelodyComparator* comparator) {
		comparator_ = comparator;
	}

private:
  Audio* audio_ = new SerialPortAudio();
  SongContainer* cur_song_ = nullptr;
	MelodyComparator* comparator_ = nullptr;

  bool is_song_played_ = false;
  int8_t current_octave_ = 4;
};

} // namespace synth
