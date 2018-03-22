#include "sound.h"
#include <stdint.h>
#include <Wire.h>
#include <Wire2.h>
#include "audio.h"

namespace synth {
namespace sound {

namespace {

void SendToneThroughWire(uint8_t dev, Audio::Tone tone) {
	if (dev < 2) {
		Wire.beginTransmission(0x24 + dev);
		Wire.write(tone);
		Wire.endTransmission();
	} else {
		Wire2.beginTransmission(0x24 + dev - 2);
		Wire2.write(tone);
		Wire2.endTransmission();
	}
}

// returns the tone but as a DTMF data
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

void SetPlayedTones(const Audio::ToneList& tones) {
	uint8_t i = 0;

	for (const auto& tone : tones) {
		SendToneThroughWire(i++, GetTone(tone));
	}
	for (; i < Audio::kMaxTones; i++) {
		SendToneThroughWire(i, 0);
	}
}

} // namespace sound
} // namespace synth
