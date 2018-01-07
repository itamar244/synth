#pragma once

#include "audio.h"
#include "song_player/song_player.h"

namespace synth {

namespace screen {
enum class Page;
}

class Environment {
public:
  Environment();
  ~Environment();

  void Tick();

  // Audio
  inline Audio* audio() const { return audio_; }
  void SetAudioType(Audio::Type type);

  // Screen
  inline const screen::Page& page() const { return page_; }
  inline void set_page(screen::Page next) {
    page_ = next;
    is_screen_painted_ = false;
  }

  inline bool ShouldPaintScreen() const { return !is_screen_painted_; }
  inline void ScreenPainted() { is_screen_painted_ = true; }

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
  screen::Page page_;

  bool is_screen_painted_ = false;
  bool is_song_played_ = false;
  int8_t octave_diff_ = 0;
};

} // namespace synth
