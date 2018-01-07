#include "audio.h"
#include <Arduino.h>
#include <stdint.h>

namespace synth {

bool Audio::AddTone(uint8_t note) {
  if (current_tones_.size() == 4) return false;
  if (GetTone(note) != current_tones_.end()) {
    current_tones_.push_back(note);
    return true;
  }
  return false;
}

bool Audio::RemoveTone(uint8_t note) {
  auto searched_note = GetTone(note);
  if (searched_note != current_tones_.end()) {
    current_tones_.erase(searched_note);
    return true;
  }
  return false;
}

// TODO: implement this after getting the part for the arduino
void BuiltinAudio::Play() const {
  if (current_tones_.empty()) return;
  for (auto& note : current_tones_) {
    Serial.print(note);
  }
  Serial.println();
}

bool SerialPortAudio::AddTone(uint8_t note) {
  if (Audio::AddTone(note)) {
    Serial.println("1" + String(note));
    return true;
  }
  return false;
}

bool SerialPortAudio::RemoveTone(uint8_t note) {
  if (Audio::RemoveTone(note)) {
    Serial.println("0" + String(note));
    return true;
  }
  return false;
}

} // namespace synth
