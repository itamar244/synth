#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <list>

namespace synth {

enum class AudioType {
  BUILTIN,
  SERIALPORT,
};

class Audio {
public:
  virtual ~Audio() {};

  virtual AudioType type() const = 0;

  virtual void play() const {};
  
  virtual void add_note(char note) = 0;
  virtual void remove_note(char note) = 0;
};

#define AUDIO_IMP_METHODS(TYPE)                                                \
  AudioType type() const { return AudioType::TYPE; }                           \
  void add_note(char note);                                                    \
  void remove_note(char note);

class BuiltinAudio: public Audio {
private:
  std::list<char> current_notes_;

public:
  AUDIO_IMP_METHODS(BUILTIN)
  void play() const;
};

class SerialPortAudio: public Audio {
public:
  AUDIO_IMP_METHODS(SERIALPORT)
};

#undef AUDIO_IMP_METHODS

} // namespace synth
