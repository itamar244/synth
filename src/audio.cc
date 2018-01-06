#include "audio.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <algorithm>
#include <list>

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

// TODO: actually implement this after getting the part for the arduino
void BuiltinAudio::Play() const {
  if (current_tones_.empty()) return;
  for (auto& note : current_tones_) {
    Serial.print(note);
  }
  Serial.println();
}

bool SerialPortAudio::AddTone(uint8_t note) {
  bool is_added = Audio::AddTone(note);
  if (is_added) {
    Serial.println("1" + String(note));
  }
  return is_added;
}

bool SerialPortAudio::RemoveTone(uint8_t note) {
  bool is_removed = Audio::RemoveTone(note);
  if (is_removed) {
    Serial.println("0" + String(note));
  }
  return is_removed;
}

} // namespace synth
