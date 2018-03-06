// Audio is an abstract object managing the current state of the played tones.
// Each Audio implementation implements specific Audio's lifecycles
// and must implement `virtual Type AudioType` to determine
// the type of handler at runtime.
//
// The following lifecycles are:
//   - `AddTone`. should always call super if inherited
//   - `RemoveTone`. should always call super even inherited
#pragma once

#include <StandardCplusplus.h>
#include <list>
#include <algorithm>
#include <stdint.h>
#include "utils.h"

namespace synth {

class Audio {
public:
	const static uint8_t kMaxTones = 4;

  enum AudioType {
    kBuiltin,
    kSerialPort,
  };

  typedef uint8_t Tone;
  typedef std::list<Tone> ToneList;

  virtual ~Audio() {}
  virtual AudioType Type() const = 0;

  virtual bool AddTone(Tone tone);
  virtual bool RemoveTone(Tone tone);

	inline const ToneList& current_tones() const {
		return current_tones_;
	}

  inline bool IsType(AudioType type) const { return Type() == type; }

	// `AddTones` and `RemoveTones` are wrappers for calling their singular functions
	// with iterable classes
	template<class Iterable>
	inline void AddTones(const Iterable& tones) {
		for (Tone tone : tones) AddTone(tone);
	}

	template<class Iterable>
	inline void RemoveTones(const Iterable& tones) {
		for (Tone tone : tones) RemoveTone(tone);
	}

protected:
  ToneList current_tones_;
};

#define AUDIO_IMPLEMENTATION_CLASS(NAME)                                       \
	class NAME ## Audio: public Audio {                                          \
	public:                                                                      \
		AudioType Type() const override { return k ## NAME; }                      \
		bool AddTone(Tone tone) override;                                          \
		bool RemoveTone(Tone tone) override;                                       \
	};
	AUDIO_IMPLEMENTATION_CLASS(Builtin)
	AUDIO_IMPLEMENTATION_CLASS(SerialPort)
#undef AUDIO_IMPLEMENTATION_CLASS

} // namespace synth
