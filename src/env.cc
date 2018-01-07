#include "env.h"
#include "audio.h"
#include "screen/pages.h"

namespace synth {

Environment::Environment()
  : page_(screen::Page::kIndex) {}

Environment::~Environment() {
  delete audio_;
}

void Environment::Tick() {
  if (is_song_played_ && !song_player_.Play(audio_)) {
    is_song_played_ = false;
  }
  if (audio_->IsType(Audio::kBuiltin)) {
    audio_->Play();
  }
}

void Environment::SetAudioType(Audio::Type type) {
  delete audio_;

  switch (type) {
    case Audio::kBuiltin:
      audio_ = new BuiltinAudio();
      break;
    case Audio::kSerialPort:
      audio_ = new SerialPortAudio();
      break;
  }
}

} // namespace synth
