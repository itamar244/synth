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
			if (state_.is_song_played	&& !comparator->Play(audio_)) {
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

void Environment::OnToneWithOctaveCall(uint8_t tone) {
	if (state_.player != nullptr) {
		if (MelodyComparator* comparator = state_.player->ToComparator()) {
				comparator->AddTonesToCompare(audio_->current_tones());
		}
	}
	if (state_.recorder != nullptr) {
		state_.recorder->PushTones(audio_->current_tones());
	}
}

} // namespace synth
