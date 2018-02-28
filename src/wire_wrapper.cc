#include "wire_wrapper.h"
#include <Wire.h>
#include <Wire2.h>

namespace synth {
namespace wire {

namespace {

#define SOUND(POSTFIX)                                                         \
	inline void Sound ## POSTFIX(uint8_t dev, uint8_t note) {                    \
		Wire ## POSTFIX.beginTransmission(0x24 + (dev % 2));                       \
		Wire ## POSTFIX.write(note);                                               \
		Wire ## POSTFIX.endTransmission();                                         \
	}
	SOUND()
	SOUND(2)
#undef SOUND

uint8_t GetTone(Audio::Tone tone) {
	switch (tone % 24) {
		case 0:  return 0x30;
		case 1:  return 0x31;
		case 2:  return 0x32;
		case 3:  return 0x33;
		case 4:  return 0x34;
		case 5:  return 0x35;
		case 6:  return 0x36;
		case 7:  return 0x37;
		case 8:  return 0x38;
		case 9:  return 0x39;
		case 10: return 0x3A;
		case 11: return 0x29;
		case 12: return 0x3B;
		case 13: return 0x3C;
		case 14: return 0x3D;
		case 15: return 0x0E;
		case 16: return 0x3E;
		case 17: return 0x2C;
		case 18: return 0x3F;
		case 19: return 0x04;
		case 20: return 0x05;
		case 21: return 0x25;
		case 22: return 0x2F;
		case 23: return 0x06;
		case 24: return 0x07;
		default: return 0;
	}
}

} // namespace

void Init() {
	Wire.begin();
	Wire2.begin();
}

void PlayTones(const Audio::ToneList tones) {
	auto tone = tones.begin();

	for (uint8_t i = 0; i < 4; i++) {
		uint8_t to_play;

		if (tone != tones.end()) {
			to_play = GetTone(*tone);
			++tone;
		} else {
			to_play = 0;
		}
		if (i < 2) {
			Sound(i, to_play);
		} else {
			Sound2(i, to_play);
		}
	}
}

} // namespace wire
} // namespace synth
