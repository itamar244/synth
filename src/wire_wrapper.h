#pragma once

#include "audio.h"

namespace synth {
namespace wire {

void Init();
void PlayTones(const Audio::ToneList& tones);

} // namespace wire
} // namespace synth