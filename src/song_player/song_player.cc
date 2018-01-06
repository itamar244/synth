#include "song_player/song_player.h"
#include <vector>
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "audio.h"

namespace synth {

void SongPlayer::Init(Song song, uint16_t size) {
  song_ = song;
  pos_ = 0;
  size_ = size;
  started_ = false;
}

void SongPlayer::ReadCurrentPhrase() {
  uint8_t notes_count = pgm_read_word_near(song_ + pos_);
  phrase_tones_.clear();
  phrase_tones_.reserve(notes_count);
  for (unsigned i = 0; i < notes_count; i++) {
    phrase_tones_.push_back(pgm_read_word_near(song_ + pos_ + i + 1));
  }
  phrase_length_ = pgm_read_word_near(song_ + pos_ + notes_count + 1);
}

bool SongPlayer::Play(Audio* audio) {
  if (pos_ >= size_) return false;
  if (!started_) {
    ReadCurrentPhrase();
    audio->AddTones(phrase_tones_);
    prev_play_millis_ = millis();
    started_ = true;
  } else if (millis() - prev_play_millis_ >= phrase_length_ * 60) {
    audio->RemoveTones(phrase_tones_);
    pos_ += phrase_tones_.size() + 2;
    if (pos_ < size_) {
      ReadCurrentPhrase();
      audio->AddTones(phrase_tones_);
      prev_play_millis_ = millis();
    }
  }
  return true;
}

} // namespace synth
