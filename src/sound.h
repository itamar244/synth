// Wrapper for DTMF's sound generation.
// Solves the limitation of I2C which can only generate 2 simultaneously sounds
// by using a synthetic I2C which can generate another 2  simultaneously sounds.
#pragma once

#include "audio.h"

namespace synth {
namespace sound {

void Init();
void SetPlayedTones(const Audio::ToneList& tones);

} // namespace sound
} // namespace synth
