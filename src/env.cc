#include "env.h"
#include "audio.h"
#include "screen/pages.h"

namespace synth {

Environment::Environment()
  : page_(screen::Page::INDEX) {}

Environment::~Environment() {
  delete audio_;
}

void Environment::tick() {
  if (is_song_played_ && !song_player_.play(audio_)) {
    is_song_played_ = false;
  }
  if (audio_->type() == AudioType::BUILTIN) {
    audio_->play();
  }
}

void Environment::set_audio_type(AudioType type) {
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
