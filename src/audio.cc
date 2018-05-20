#include "audio.h"
#include <Arduino.h>
#include <stdint.h>
#include "utils.h"
#include "serial_communication.h"
#include "sound.h"

namespace synth {

bool Audio::AddTone(Tone tone) {
  if (current_tones_.size() == kMaxTones) return false;
  if (!utils::HasItem(current_tones_, tone)) {
    current_tones_.push_back(tone);
    return true;
  }
  return false;
}

bool Audio::RemoveTone(Tone tone) {
  auto searched_tone = utils::FindItem(current_tones_, tone);
  if (searched_tone != current_tones_.end()) {
    current_tones_.erase(searched_tone);
    return true;
  }
  return false;
}

// wrapper for all tone lifecycles. receives a audio class's prefix name
// and a macro method to call on update with the lifecycle type
#define TONE_LIFECYLCES(CLASS, V)                                              \
	__CREATOR(CLASS, Add, V)                                                     \
	__CREATOR(CLASS, Remove, V)

#define __CREATOR(CLASS, FUNC, V)                                              \
	bool CLASS ## Audio::FUNC ## Tone(Tone tone) {                               \
		bool updated_tones = Audio::FUNC ## Tone(tone);                            \
		/* V's call is inside a block for potentially a multi line code */         \
		if (updated_tones) { V(FUNC) }                                             \
		return updated_tones;                                                      \
	}

#define V(_) sound::SetPlayedTones(current_tones_);
	TONE_LIFECYLCES(Builtin, V)
#undef V

#define V(FUNC) serial::Send(serial::k ## FUNC ## Tone, tone);
	TONE_LIFECYLCES(SerialPort, V)
#undef V

} // namespace synth
