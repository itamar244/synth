#include "audio.h"
#include <Arduino.h>
#include <stdint.h>

namespace synth {

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

bool SerialPortAudio::AddTone(uint8_t tone) {
	if (Audio::AddTone(tone)) {
		char stream[] = {1, char(tone)};
		Serial.write(stream, 2);
		return true;
	}
	return false;
}

bool SerialPortAudio::RemoveTone(uint8_t tone) {
  if (Audio::RemoveTone(tone)) {
    char stream[] = {0, char(tone)};
    Serial.write(stream, 2);
    return true;
  }
  return false;
}

} // namespace synth
