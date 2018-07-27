#include "./env.h"
// #include "audio.h"
// #include "serial_communication.h"

namespace synth {

Environment::~Environment() {
	// if (player_ != nullptr) utils::DeletePtr(player_);
	// if (recorder_ != nullptr) utils::DeletePtr(recorder_);
  // delete audio_;
}

void Environment::Tick() {
	// if (player_ != nullptr) {
	// 	if (MelodyComparator* comparator = player_->ToComparator()) {
	// 		if (is_song_played_	&& !comparator->Play(audio_)) {
	// 			is_song_played_ = false;
	// 		}
	// 	} else if (!player_->Play(audio_)) {
	// 		utils::DeletePtr(player_);
	// 	}
	// }
}
//
// void Environment::SetAudioType(Audio::AudioType type) {
//   delete audio_;
//
//   switch (type) {
//     case Audio::kBuiltin:
//       audio_ = new BuiltinAudio();
//       break;
//     case Audio::kSerialPort:
//       audio_ = new SerialPortAudio();
//       break;
//   }
// }
//
// void Environment::DeletePlayer() {
// 	if (player_ == nullptr) return;
//
// 	audio_->RemoveNotes(GetPlayerCurrentNotes(player_));
//
// 	utils::DeletePtr(player_);
// }
//
// std::pair<bool, float> Environment::ComparatorNextSection() {
// 	if (player_ == nullptr) return {false, 0};
//
// 	if (MelodyComparator* comparator = player_->ToComparator()) {
// 		if (comparator->NextSection()) {
// 			is_song_played_ = true;
// 			return {true, 0};
// 		}
//
// 		return {false, comparator->grade()};
// 	}
//
// 	return {false, 0};
// }
//
// void Environment::OnNoteWithOctaveCall(uint8_t note) {
// 	if (player_ != nullptr) {
// 		if (MelodyComparator* comparator = player_->ToComparator()) {
// 				comparator->AddNotesToCompare(audio_->current_notes());
// 		}
// 	}
// 	if (recorder_ != nullptr) {
// 		recorder_->PushNotes(audio_->current_notes());
// 	}
// }

} // namespace synth
