#pragma once

#include <stdint.h>
#include <vector>
#include "audio.h"
#include "sound_phrase.h"

namespace synth {

class SongPlayer {
public:
  typedef std::vector<SoundPhrase> Song;

  void init(const Song& song);
  bool play(Audio* audio);
  void Init(const Song& song);
  bool Play(Audio* audio);

private:
  Song song_;
  uint16_t pos_;
  uint32_t prev_play_millis_;
  bool started_;
};

} // namespace synth
