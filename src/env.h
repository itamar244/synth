#pragma once

#include "audio.h"
#include "song_player/song_player.h"

namespace synth {

namespace screen {
enum class Page;
}

class Environment {
public:
  ~Environment();

  void Tick();

  // Audio
  inline Audio* audio() const { return audio_; }
  void SetAudioType(Audio::Type type);

  // Song
  inline uint8_t AddOctaveDiff(uint8_t note) {
    return note + octave_diff_ * 12;
  }
  inline void ToggleOctaveLevel() { octave_diff_ = !octave_diff_; }
  inline void PlaySong(SongPlayer::Song song, uint16_t size) {
    song_player_.Init(song, size);
    is_song_played_ = true;
  }

private:
  Audio* audio_ = new SerialPortAudio();
  SongPlayer song_player_;

  bool is_song_played_ = false;
  int8_t octave_diff_ = 0;
};

} // namespace synth
