#include "pgm_song_parser.h"
#include <avr/pgmspace.h>

namespace synth {

using PGMPhrase = PGMSongParser::PGMPhrase;

PGMSongParser::PGMSongParser(const SongContainer& container)
	: song_(container.song)
	, size_(container.size)
	, pos_(0) {}

void PGMSongParser::ParseNextPhrase() {
  uint8_t tones_count = pgm_read_word_near(song_ + pos_);
  phrase_.tones.resize(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase_.tones[i] = pgm_read_word_near(song_ + pos_ + i + 1);
  }
  phrase_.length =
		pgm_read_word_near(song_ + pos_ + tones_count + 1);
	pos_ += phrase_.tones.size() + 2;
}

PGMPhrase PGMSongParser::ParsePhraseAt(uint16_t pos) {
	PGMPhrase phrase;
	uint8_t tones_count = pgm_read_word_near(song_ + pos);

  phrase.tones.reserve(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase.tones.push_back(pgm_read_word_near(song_ + pos + i + 1));
  }
  phrase.length = pgm_read_word_near(song_ + pos + tones_count + 1);
	return phrase;
}

} // namespace synth
