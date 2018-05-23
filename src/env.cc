#include "env.h"
#include "audio.h"
#include "serial_communication.h"

namespace synth {

State::~State() {
	if (player != nullptr) utils::DeletePtr(player);
	if (recorder != nullptr) utils::DeletePtr(recorder);
}

Environment::~Environment() {
  delete audio_;
}

void Environment::Tick() {
	auto& player = state_.player;
	if (player != nullptr) {
		if (MelodyComparator* comparator = player->ToComparator()) {
			if (state_.is_song_played
					&& !comparator->Play(audio_)) {
				state_.is_song_played = false;
			}
		} else if (!player->Play(audio_)) {
			utils::DeletePtr(player);
		}
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
