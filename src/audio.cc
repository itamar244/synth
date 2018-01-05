#include "audio.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <algorithm>

namespace synth {

void BuiltinAudio::play() const {
  if (current_notes_.empty()) return;
  for (auto& note : current_notes_) {
    Serial.print(note);
  }
  Serial.println();
}

void BuiltinAudio::add_note(char note) {
  if (current_notes_.size() == 4) return;
  auto notes_end = current_notes_.end();
  if (std::find(current_notes_.begin(), notes_end, note) == notes_end) {
    current_notes_.push_back(note);
  }
}

void BuiltinAudio::remove_note(char note) {
  current_notes_.remove(note);
}

void SerialPortAudio::add_note(char note) {
  Serial.println("1" + String(note));
}

void SerialPortAudio::remove_note(char note) {
  Serial.println("0" + String(note));
}

} // namespace synth
