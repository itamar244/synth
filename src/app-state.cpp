#include "app-state.h"
#include "audio.h"

namespace synth {

AppState::~AppState() {
  delete audio_controller_;
}

void AppState::change_audio_controller(AudioMode mode) {
  delete audio_controller_;

  switch (mode) {
    case AudioMode::BUILTIN:
      audio_controller_ = new BuiltinAudio();
      break;
    case AudioMode::SERIALPORT:
      audio_controller_ = new SerialPortAudio();
      break;
  }
}

} // namespace synth
