#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace synth {

inline void SetLedBulbColor(uint8_t r, uint8_t g, uint8_t b) {
	analogWrite(3, r);
	analogWrite(5, g);
	analogWrite(5, b);
}

inline void ClearLedBulb() {
	SetLedBulbColor(0, 0, 0);
}

} // namespace synth
