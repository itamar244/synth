#include "env.h"
#include "audio.h"
#include "serial_communication.h"

namespace synth {

Environment::~Environment() {
  delete audio_;
	if (comparator_ != nullptr) {
		delete comparator_;
	}
}

void Environment::Tick() {
  if (is_song_played_
			&& comparator_ != nullptr
			&& !comparator_->Play(audio_)) {
    is_song_played_ = false;
  }
	if (records_player_ != nullptr && !records_player_->Play(audio_)) {
		utils::DeletePtr(records_player_);
	}
}

void Environment::SetAudioType(Audio::AudioType type) {
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
