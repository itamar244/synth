#include "song_player/song_player.h"
#include <Arduino.h>
#include "audio.h"

namespace synth {

const uint8_t kTime32nd = 60;

void SongPlayer::Init(Song song, uint16_t size) {
	PGMSongParser::Init(song, size);
	started_ = false;
	ended_ = false;
}

bool SongPlayer::Play(Audio* audio) {
  if (ended_) return false;

  if (!started_) {
    ParseNextPhrase();
    audio->AddTones(phrase_.tones);
    prev_play_millis_ = millis();
    started_ = true;
  } else if (millis() - prev_play_millis_ >= phrase_.length * kTime32nd) {
    audio->RemoveTones(phrase_.tones);
    if (HasNextPhrase()) {
      ParseNextPhrase();
      audio->AddTones(phrase_.tones);
      prev_play_millis_ = millis();
    } else {
			ended_ = true;
		}
  }
  return true;
}

} // namespace synth
