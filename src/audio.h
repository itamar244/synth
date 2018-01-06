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
  
  virtual bool add_note(char note);
  virtual bool remove_note(char note);
  

  inline bool has_note(char note) {
    auto end = current_notes_.end();
    return std::find(current_notes_.begin(), end, note) != end;
  }
  inline bool add_note(const SoundPhrase& phrase) { 
    return add_note(phrase.note); 
  }
  inline bool remove_note(const SoundPhrase& phrase) { 
    return remove_note(phrase.note); 
  }

protected:
  std::list<char> current_notes_;
};

#define AUDIO_IMP_METHODS(TYPE)                                                \
  AudioType type() const { return AudioType::TYPE; }                           \
  bool add_note(char note);                                                    \
  bool remove_note(char note);

class BuiltinAudio: public Audio {
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
