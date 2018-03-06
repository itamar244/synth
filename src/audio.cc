#include "audio.h"
#include <Arduino.h>
#include <stdint.h>
#include "serial_communication.h"
#include "wire_wrapper.h"

namespace synth {

using serial::Send;

bool Audio::AddTone(Tone tone) {
  if (current_tones_.size() == kMaxTones) return false;
  if (!utils::HasItem(current_tones_, tone)) {
    current_tones_.push_back(tone);
    return true;
  }
  return false;
}

bool Audio::RemoveTone(Tone tone) {
  auto searched_tone = utils::FindItem(current_tones_, tone);
  if (searched_tone != current_tones_.end()) {
    current_tones_.erase(searched_tone);
    return true;
  }
  return false;
}

#define BUILTIN_CALL_TONE_CHANGE(FUNC)                                         \
	bool BuiltinAudio::FUNC ## Tone(uint8_t tone) {                              \
		if (Audio::FUNC ## Tone(tone)) {                                           \
			wire::PlayTones(current_tones_);                                         \
		}                                                                          \
		return false;                                                              \
	}
	BUILTIN_CALL_TONE_CHANGE(Add)
	BUILTIN_CALL_TONE_CHANGE(Remove)
#undef BUILTIN_CALL_TONE_CHANGE

#define SERIALPORT_CALL_TONE_CHANGE(FUNC)                                      \
	bool SerialPortAudio::FUNC ## Tone(uint8_t tone) {                           \
		if (Audio::FUNC ## Tone(tone)) {                                           \
			Send(serial::k ## FUNC ## Tone, tone);                                   \
			return true;                                                             \
		}                                                                          \
		return false;                                                              \
	}
	SERIALPORT_CALL_TONE_CHANGE(Add)
	SERIALPORT_CALL_TONE_CHANGE(Remove)
#undef SERIALPORT_CALL_TONE_CHANGE

} // namespace synth
