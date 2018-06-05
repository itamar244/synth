#include "melody_player/parser.h"
#include <avr/pgmspace.h>
#include "phrase.h"

namespace synth {

MelodyParser::MelodyParser(const MelodyContainer& container)
	: melody_(container.melody)
	, pos_(0) {}

void MelodyParser::ParsePhrase() {
  uint8_t tones_count = melody_[pos_];
  phrase_.tones.resize(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase_.tones[i] = melody_[pos_ + i + 1];
  }
  phrase_.length = melody_[pos_ + tones_count + 1];
}

void MelodyParser::NextPhrase() {
	pos_ += phrase_.tones.size() + 2;
}

Phrase MelodyParser::ParsePhraseAt(uint16_t pos) {
	Phrase phrase;
	uint8_t tones_count = melody_[pos];

  phrase.tones.reserve(tones_count);
  for (uint8_t i = 0; i < tones_count; i++) {
    phrase.tones.push_back(melody_[pos + i + 1]);
  }
  phrase.length = melody_[pos + tones_count + 1];
	return phrase;
}

} // namespace synth
