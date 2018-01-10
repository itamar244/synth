#pragma once

#include <stdint.h>
#include <vector>
#include "audio.h"
#include "song_player/pgm_song_parser.h"

namespace synth {

class SongPlayer: public PGMSongParser {
public:
  void Init(Song song, uint16_t size);
  bool Play(Audio* audio);

private:
  uint32_t prev_play_millis_;
  bool started_;
	bool ended_;
};

} // namespace synth
