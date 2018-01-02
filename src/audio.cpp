#include "audio.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <algorithm>

namespace synth {

void BuiltinAudio::start_note(char note) {
  if (current_notes_size_ == SYNTH_MAX_PLAYED_NOTES) return;
  char* notes_end = &current_notes_[current_notes_size_];
  if (std::find(&current_notes_[0], notes_end, note) == notes_end) {
    current_notes_[current_notes_size_++] = note;
  }
}

void BuiltinAudio::stop_note(char note) {
  char* notes_end = &current_notes_[current_notes_size_];
  char* to_stop = std::find(&current_notes_[0], notes_end, note);
  if (to_stop != notes_end) {
    *to_stop = 0;
    for (char* cur_note = to_stop + 1; to_stop != notes_end; cur_note++) {
      *(cur_note - 1) = *cur_note;
    }
    current_notes_size_--;
  }
}

void SerialPortAudio::start_note(char note) {
  Serial.println("p" + String(note));
}

void SerialPortAudio::stop_note(char note) {
  Serial.println("u" + String(note));
}

} // namespace synth
