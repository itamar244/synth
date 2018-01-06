#pragma once

#include <stdint.h>
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

  virtual AudioType Type() const = 0;

  virtual void Play() const {};
  
  virtual bool AddTone(uint8_t note);
  virtual bool RemoveTone(uint8_t note);
  

  inline std::list<uint8_t>::iterator GetTone(uint8_t tone) {
    return std::find(current_tones_.begin(), current_tones_.end(), tone);
  }
#define CALL_WITH_VECTOR(FUNC)                                                 \
  template<class List>                                                         \
  inline bool FUNC ## Tones(const List& tones) {                               \
    for (uint8_t tone : tones) {                                               \
      if (!FUNC ## Tone(tone)) return false;                                   \
    }                                                                          \
    return true;                                                               \
  }
  CALL_WITH_VECTOR(Add) CALL_WITH_VECTOR(Remove)
#undef CALL_WITH_VECTOR

protected:
  std::list<uint8_t> current_tones_;
};

#define AUDIO_IMP_METHODS(TYPE)                                                \
  AudioType Type() const { return AudioType::TYPE; }                           \
  bool AddTone(uint8_t note);                                                  \
  bool RemoveTone(uint8_t note);

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
