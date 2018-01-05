#include "app-state.h"
#include "audio.h"
#include "screen/pages.h"

namespace synth {

AppState::AppState()
  : page_(screen::Page::INDEX) {}

AppState::~AppState() {
  delete audio_;
}

void AppState::change_audio_controller(AudioType type) {
  delete audio_;

  switch (type) {
    case AudioType::BUILTIN:
      audio_ = new BuiltinAudio();
      break;
    case AudioType::SERIALPORT:
      audio_ = new SerialPortAudio();
      break;
  }
}

} // namespace synth
