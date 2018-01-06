#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <list>
#include "sound_phrase.h"

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
  virtual void add_note(const SoundPhrase& phrase) = 0;
  virtual void remove_note(const SoundPhrase& phrase) = 0;
};

#define AUDIO_IMP_METHODS(TYPE)                                                \
  AudioType type() const { return AudioType::TYPE; }                           \
  void add_note(char note);                                                    \
  void remove_note(char note);                                                 \
  void add_note(const SoundPhrase& phrase) { add_note(phrase.note); }          \
  void remove_note(const SoundPhrase& phrase) { remove_note(phrase.note); }

class BuiltinAudio: public Audio {
public:
  AUDIO_IMP_METHODS(BUILTIN)
  void play() const;

private:
  std::list<char> current_notes_;
};

class SerialPortAudio: public Audio {
public:
  AUDIO_IMP_METHODS(SERIALPORT)
};

#undef AUDIO_IMP_METHODS

} // namespace synth
