#include "parser.h"
#include "../phrase.h"

namespace synth {

MelodyParser::MelodyParser(const MelodyContainer& container)
	: melody_(container.melody)
	, pos_(0) {}

void MelodyParser::ParsePhrase() {
  uint8_t notes_count = melody_[pos_];
  phrase_.notes.clear();
  for (uint8_t i = 0; i < notes_count; i++) {
    phrase_.notes.push_back(melody_[pos_ + i + 1]);
  }
  phrase_.length = melody_[pos_ + notes_count + 1];
}

void MelodyParser::NextPhrase() {
	pos_ += phrase_.notes.size() + 2;
}

Phrase MelodyParser::ParsePhraseAt(uint16_t pos) {
	Phrase phrase;
	uint8_t notes_count = melody_[pos];

  for (uint8_t i = 0; i < notes_count; i++) {
    phrase.notes.push_back(melody_[pos + i + 1]);
  }
  phrase.length = melody_[pos + notes_count + 1];
	return phrase;
}

} // namespace synth
