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

  virtual AudioType Type() const = 0;

  virtual void Play() const {};
  
  virtual bool AddNote(char note);
  virtual bool RemoveNote(char note);
  

  inline bool HasNote(char note) {
    auto end = current_notes_.end();
    return std::find(current_notes_.begin(), end, note) != end;
  }
#define CALL_WITH_PHRASE(FUNC)                                                 \
  inline bool FUNC ## Phrase(const SoundPhrase& phrase) {                      \
    for (auto& note : phrase.notes) {                                          \
      if (!FUNC ## Note(note)) return false;                                   \
    }                                                                          \
    return true;                                                               \
  }
  CALL_WITH_PHRASE(Add) CALL_WITH_PHRASE(Remove)
#undef CALL_WITH_PHRASE

protected:
  std::list<char> current_notes_;
};

#define AUDIO_IMP_METHODS(TYPE)                                                \
  AudioType Type() const { return AudioType::TYPE; }                           \
  bool AddNote(char note);                                                     \
  bool RemoveNote(char note);

class BuiltinAudio: public Audio {
public:
  AUDIO_IMP_METHODS(BUILTIN)
  void Play() const;
};

class SerialPortAudio: public Audio {
public:
  AUDIO_IMP_METHODS(SERIALPORT)
};

#undef AUDIO_IMP_METHODS

} // namespace synth
