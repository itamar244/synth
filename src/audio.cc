#include "audio.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <algorithm>
#include <list>

namespace synth {

bool Audio::add_note(char note) {
  if (current_notes_.size() == 4) return false;
  if (!has_note(note)) {
    current_notes_.push_back(note);
    return true;
  }
  return false;
}

bool Audio::remove_note(char note) {
  auto end = current_notes_.end();
  auto searched_note = std::find(current_notes_.begin(), end, note);
  if (searched_note != end) {
    current_notes_.erase(searched_note);
    return true;
  }
  return false;
}

// TODO: actually implement this after getting the part for the arduino
void BuiltinAudio::play() const {
  if (current_notes_.empty()) return;
  for (auto& note : current_notes_) {
    Serial.print(note);
  }
  Serial.println();
}

bool SerialPortAudio::add_note(char note) {
  bool is_added = Audio::add_note(note);
  if (is_added) {
    Serial.println("1" + String(note));
  }
  return is_added;
}

bool SerialPortAudio::remove_note(char note) {
  bool is_removed = Audio::remove_note(note);
  if (is_removed) {
    Serial.println("0" + String(note));
  }
  return is_removed;
}

} // namespace synth
