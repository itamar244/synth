#include "song_player/song_player.h"
#include <vector>
// #include <avr/pgmspace.h>
#include "audio.h"

namespace synth {

void SongPlayer::init(const Song& song) {
  song_ = song;
  pos_ = 0;
  started_ = false;
}

bool SongPlayer::play(Audio* audio) {
  const auto& size = song_.size();
  if (pos_ >= size) return false;
  SoundPhrase& phrase = song_[pos_];
  if (!started_) {
    audio->add_note(phrase);
    started_ = true;
    prev_play_millis_ = millis();
  } else if (millis() - prev_play_millis_ >= phrase.length * 60) {
    if (phrase.note != 'H') audio->remove_note(phrase);
    pos_++;
    if (pos_ < size) {
      phrase = song_[pos_];
      if (phrase.note != 'H') audio->add_note(phrase);
      prev_play_millis_ = millis();
    }
  }
  return true;
}

} // namespace synth
