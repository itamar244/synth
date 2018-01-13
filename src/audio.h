#pragma once

#include <StandardCplusplus.h>
#include <list>
#include <algorithm>
#include <stdint.h>

namespace synth {


class Audio {
public:
  enum Type {
    kBuiltin,
    kSerialPort,
  };

  typedef uint8_t Tone;
  typedef std::list<Tone> ToneList;

  virtual ~Audio() {};
  virtual Type AudioType() const = 0;
  inline bool IsType(Type type) {
    return AudioType() == type;
  }
  virtual void Play() const {};

  virtual bool AddTone(Tone tone);
  virtual bool RemoveTone(Tone tone);

	inline const ToneList& current_tones() const {
		return current_tones_;
	}
  inline ToneList::iterator GetTone(Tone tone) {
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
  ToneList current_tones_;
};

class BuiltinAudio: public Audio {
public:
  Type AudioType() const override { return kBuiltin; }
  void Play() const override;
};

class SerialPortAudio: public Audio {
public:
  Type AudioType() const override { return kSerialPort; }
  bool AddTone(Tone tone) override;
  bool RemoveTone(Tone tone) override;
};

} // namespace synth
