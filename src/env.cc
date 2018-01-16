#include "env.h"
#include "audio.h"

namespace synth {

Environment::~Environment() {
  delete audio_;
	if (comparator_ != nullptr) {
		delete comparator_;
	}
}

void Environment::Tick() {
  if (
			is_song_played_
			&& comparator_ != nullptr
			&& !comparator_->Play(audio_)) {
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
