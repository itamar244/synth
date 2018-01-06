#pragma once

#include "audio.h"
#include "song_player/song_player.h"

namespace synth {

namespace screen {
enum class Page;
}

class Environment {
private:
  Audio* audio_ = new SerialPortAudio();
  SongPlayer song_player_;
  screen::Page page_;

  bool is_screen_painted_ = false;
  bool is_song_played_ = false;

public:
  Environment();
  ~Environment();

  void tick();

  // Audio
  inline Audio* audio() const { return audio_; }
  void set_audio_type(AudioType type);

  // Screen
  inline const screen::Page& get_page() const { return page_; }
  inline void switch_page(screen::Page next) {
    page_ = next;
    is_screen_painted_ = false;
  }

  inline bool should_paint_screen() const { return !is_screen_painted_; }
  inline void screen_painted() { is_screen_painted_ = true; }

  // Song
  inline void play_song(const SongPlayer::Song& song) {
    song_player_.init(song);
    is_song_played_ = true;
  }
};

} // namespace synth
