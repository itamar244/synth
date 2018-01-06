#pragma once

#include <stdint.h>
#include <vector>
#include "audio.h"

namespace synth {

class SongPlayer {
public:
  typedef const uint8_t* Song;

  void Init(Song song, uint16_t size);
  bool Play(Audio* audio);

private:
  Song song_;
  std::vector<uint8_t> phrase_tones_;
  uint8_t phrase_length_;
  uint16_t pos_;
  uint16_t size_;
  uint32_t prev_play_millis_;
  bool started_;

  void ReadCurrentPhrase();
};

} // namespace synth
