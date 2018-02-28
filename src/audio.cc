#include "audio.h"
#include <Arduino.h>
#include <stdint.h>
#include "serial_communication.h"

namespace synth {

using serial::Send;

bool Audio::AddTone(uint8_t tone) {
  if (current_tones_.size() == 4) return false;
  if (GetTone(tone) == current_tones_.end()) {
    current_tones_.push_back(tone);
    return true;
  }
  return false;
}

bool Audio::RemoveTone(uint8_t tone) {
  auto searched_tone = GetTone(tone);
  if (searched_tone != current_tones_.end()) {
    current_tones_.erase(searched_tone);
    return true;
  }
  return false;
}

// TODO: implement this after getting the part for the arduino
void BuiltinAudio::Play() const {
  if (current_tones_.empty()) return;
  for (auto& tone : current_tones_) {
    Serial.print(tone);
  }
  Serial.println();
}


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
