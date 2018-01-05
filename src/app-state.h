#pragma once

#include "audio.h"
#include "screen/page.h"

namespace synth {

class AppState {
private:
  Audio* audio_ = new SerialPortAudio();
  screen::Page page_ = screen::Page::INDEX;
  bool is_screen_painted_ = false;

public:
  ~AppState();

  // Audio
  inline Audio* audio() const { return audio_; }
  void change_audio_controller(AudioType mode);

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
