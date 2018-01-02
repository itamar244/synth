#pragma once

#include <Arduino.h>

namespace synth {

#define SYNTH_MAX_PLAYED_NOTES 4

class AudioController {
public:
  virtual ~AudioController() {};
  virtual void start_note(char note) = 0;
  virtual void stop_note(char note) = 0;
};

class SerialPortAudioController: public AudioController {
public:
  void start_note(char note);
  void stop_note(char note);
};

class BuiltinAudioController: public AudioController {
private:
  char current_notes_[SYNTH_MAX_PLAYED_NOTES]  = {0};
  uint8_t current_notes_size_ = 0;

public:
  void start_note(char note);
  void stop_note(char note);
};

} // namespace synth
