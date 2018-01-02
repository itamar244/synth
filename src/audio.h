#pragma once

#include <Arduino.h>

#define SYNTH_MAX_PLAYED_NOTES 4

namespace synth {

enum class AudioMode {
  BUILTIN,
  SERIALPORT,
};

class Audio {
public:
  virtual ~Audio() {};
  virtual void start_note(char note) = 0;
  virtual void stop_note(char note) = 0;
};

class BuiltinAudio: public Audio {
private:
  char current_notes_[SYNTH_MAX_PLAYED_NOTES];
  uint8_t current_notes_size_ = 0;

public:
  void start_note(char note);
  void stop_note(char note);
};

class SerialPortAudio: public Audio {
public:
  void start_note(char note);
  void stop_note(char note);
};

} // namespace synth
