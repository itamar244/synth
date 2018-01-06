#include "song_player/song_player.h"
#include <vector>
#include <avr/pgmspace.h>
#include "audio.h"

namespace synth {

inline char NoteFromPos(uint8_t pos) {
  return pos > 5 ? 'A' + pos - 6 : 'C' + (pos - 1);
}

SongPlayer::~SongPlayer() {
  if (current_phrase_ != nullptr) {
    delete current_phrase_;
  }
}

void SongPlayer::Init(Song song, uint16_t size) {
  song_ = song;
  pos_ = 0;
  size_ = size;
}

void SongPlayer::ReadCurrentPhrase() {
  uint8_t notes_count = pgm_read_word_near(song_ + pos_);
  std::vector<char> notes;
  notes.reserve(notes_count);
  for (unsigned i = 0; i < notes_count; i++) {
    notes.push_back(
      NoteFromPos(pgm_read_word_near(song_ + pos_ + i + 1)));
  }
  if (current_phrase_ != nullptr) delete current_phrase_;
  current_phrase_ = new SoundPhrase{
    notes,
    pgm_read_word_near(song_ + pos_ + notes_count + 1),
  };
}

bool SongPlayer::Play(Audio* audio) {
  if (pos_ >= size_) return false;
  if (current_phrase_ == nullptr) {
    ReadCurrentPhrase();
    audio->AddPhrase(*current_phrase_);
    prev_play_millis_ = millis();
  } else if (millis() - prev_play_millis_ >= current_phrase_->length * 60) {
    audio->RemovePhrase(*current_phrase_);
    pos_ += current_phrase_->notes.size() + 2;
    if (pos_ < size_) {
      ReadCurrentPhrase();
      audio->AddPhrase(*current_phrase_);
      prev_play_millis_ = millis();
    }
  }
  return true;
}

} // namespace synth
