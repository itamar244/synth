#pragma once

#include "audio.h"
#include "screen/page.h"

namespace synth {

class AppState {
private:
  Audio* audio_controller_ = new SerialPortAudio();
  AudioMode audio_mode_ = AudioMode::SERIALPORT;
  screen::Page page_ = screen::Page::INDEX;
  bool is_screen_painted_ = false;

public:
  ~AppState();

  // Audio
  void change_audio_controller(AudioMode mode);
  inline void start_note(char note) { audio_controller_->start_note(note); }
  inline void stop_note(char note) { audio_controller_->stop_note(note); }

  // Screen
  inline const screen::Page& get_page() const { return page_; }
  inline void switch_page(screen::Page next) {
    page_ = next;
    is_screen_painted_ = false;
  }

  inline bool should_paint_screen() const { return !is_screen_painted_; }
  inline void screen_painted() { is_screen_painted_ = true; }
};

} // namespace synth
