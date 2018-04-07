#include "melody_player/parser.h"
#include <avr/pgmspace.h>

namespace synth {

using Phrase = MelodyParser::Phrase;

MelodyParser::MelodyParser(const MelodyContainer& container)
	: melody_(container.melody)
	, size_(container.size)
	, pos_(0) {}

void MelodyParser::ParseNextPhrase() {
  uint8_t tones_count = pgm_read_word_near(melody_ + pos_);
  phrase_.tones.resize(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase_.tones[i] = pgm_read_word_near(melody_ + pos_ + i + 1);
  }
  phrase_.length =
		pgm_read_word_near(melody_ + pos_ + tones_count + 1);
	pos_ += phrase_.tones.size() + 2;
}

Phrase MelodyParser::ParsePhraseAt(uint16_t pos) {
	Phrase phrase;
	uint8_t tones_count = pgm_read_word_near(melody_ + pos);

  phrase.tones.reserve(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase.tones.push_back(pgm_read_word_near(melody_ + pos + i + 1));
  }
  phrase.length = pgm_read_word_near(melody_ + pos + tones_count + 1);
	return phrase;
}

} // namespace synth
