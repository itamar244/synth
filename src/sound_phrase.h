#pragma once

#include <vector>
#include <stdint.h>

namespace synth {

struct SoundPhrase {
  std::vector<char> notes;
  uint8_t length;
};

} // namespace synth
