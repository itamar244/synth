#include "pgm_song_parser.h"
#include <avr/pgmspace.h>

namespace synth {

void PGMSongParser::Init(Song song, uint16_t size) {
	song_ = song;
	size_ = size;
	pos_ = 0;
}

void PGMSongParser::ParseNextPhrase() {
  uint8_t tones_count = pgm_read_word_near(song_ + pos_);
  phrase_.tones.resize(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase_.tones[i] = pgm_read_word_near(song_ + pos_ + i + 1);
  }
  phrase_.length = pgm_read_word_near(song_ + pos_ + tones_count + 1);
	pos_ += phrase_.tones.size() + 2;
}

} // namespace synth
