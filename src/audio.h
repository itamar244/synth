// Audio is an abstract object managing the current state of the played tones.
// Each Audio implementation implements specific Audio's lifecycles
// and must implement `virtual Type AudioType` to determine
// the type of handler at runtime.
//
// The following lifecycles are:
//   - `AddTone`. should always call super if inherited
//   - `RemoveTone`. should always call super even inherited
//   - `Play`. called in every arduino's tick. should output sounds if needded
#pragma once

#include <StandardCplusplus.h>
#include <list>
#include <algorithm>
#include <stdint.h>
#include "utils.h"

namespace synth {

class Audio {
public:
  enum AudioType {
    kBuiltin,
    kSerialPort,
  };

  typedef uint8_t Tone;
  typedef std::list<Tone> ToneList;

  virtual ~Audio() {};
  virtual AudioType Type() const = 0;
  virtual void Play() const {};

  virtual bool AddTone(Tone tone);
  virtual bool RemoveTone(Tone tone);

	inline const ToneList& current_tones() const {
		return current_tones_;
	}

  inline bool IsType(AudioType type) { return Type() == type; }

  inline ToneList::iterator GetTone(Tone tone) {
    return utils::FindItem(current_tones_, tone);
  }

	// `AddTones` and `RemoveTones` are wrappers for calling their singular functions
	// with iterable classes
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
  AudioType Type() const override { return kBuiltin; }
  void Play() const override;
};

class SerialPortAudio: public Audio {
public:
  AudioType Type() const override { return kSerialPort; }
  bool AddTone(Tone tone) override;
  bool RemoveTone(Tone tone) override;
};

} // namespace synth
