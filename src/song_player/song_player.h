#pragma once

#include <stdint.h>
#include <vector>
#include "audio.h"
#include "sound_phrase.h"

namespace synth {

class SongPlayer {
public:
  typedef const uint8_t* Song;

  ~SongPlayer();
  void Init(Song song, uint16_t size);
  bool Play(Audio* audio);

private:
  Song song_;
  SoundPhrase* current_phrase_ = nullptr;
  uint16_t pos_;
  uint16_t size_;
  uint32_t prev_play_millis_;

  void ReadCurrentPhrase();
};

} // namespace synth
