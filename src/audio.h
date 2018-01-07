#pragma once

#include <StandardCplusplus.h>
#include <list>
#include <algorithm>
#include <stdint.h>

namespace synth {

enum class AudioType {
  BUILTIN,
  SERIALPORT,
};

class Audio {
public:
  typedef uint8_t Tone;

  virtual ~Audio() {};
  virtual AudioType Type() const = 0;
  inline bool IsType(AudioType type) {
    return Type() == type;
  }
  virtual void Play() const {};
  
  virtual bool AddTone(Tone tone);
  virtual bool RemoveTone(Tone tone);
  
  inline std::list<Tone>::iterator GetTone(Tone tone) {
    return std::find(current_tones_.begin(), current_tones_.end(), tone);
  }
  
  #define CALL_WITH_ITERABLE(FUNC)                                               \
    template<class Iterable>                                                     \
    inline void FUNC ## Tones(const Iterable& tones) {                           \
      for (Tone tone : tones) {                                                  \
        FUNC ## Tone(tone);                                                      \
      }                                                                          \
    }
    CALL_WITH_ITERABLE(Add) CALL_WITH_ITERABLE(Remove)
  #undef CALL_WITH_ITERABLE

protected:
  std::list<Tone> current_tones_;
};

class BuiltinAudio: public Audio {
public:
  AudioType Type() const override { return AudioType::BUILTIN; }
  void Play() const override;
};

class SerialPortAudio: public Audio {
public:
  AudioType Type() const override { return AudioType::SERIALPORT; }
  bool AddTone(Tone tone) override;
  bool RemoveTone(Tone tone) override;
};

} // namespace synth
