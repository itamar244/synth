#include "parser.h"
#include <cctype>
#include <cstdlib>
#include <string>
#include <iostream>
#include "../audio.h"

namespace synth {

namespace {

const storage::Path kMelodiesPath = "./melodies-data";
const std::map<char, std::size_t> kNotes({
	{'C', 0}, {'D', 2}, {'E', 4}, {'F', 5}, {'G', 7}, {'A', 0}, {'B', 11},
});

float GetNumber(char const* value, std::size_t& pos) {
	bool hasDot = false;
	std::size_t start = pos;

	for (;;) {
		char ch = value[pos];

		if (std::isdigit(ch)) {
			pos += 1;
		} else if (ch == '.' && !hasDot) {
			pos += 1;
			hasDot = true;
		} else {
			break;
		}
	}

	return std::atof(std::string(value, start, pos - start).c_str());
}

Phrase ParsePhraseFromString(char const* value) {
	std::size_t pos = 0, size = std::strlen(value);
	Audio::NoteList notes;

	float phrase_length = 0;

	while (value[pos] != ',') {
		while (value[pos] == ' ') ++pos;
		phrase_length += 32 / GetNumber(value, pos);
	}
	pos++;

	while (pos < size) {
		while (value[pos] == ' ') ++pos;
		uint8_t note = kNotes.at(value[pos++]);
		if (!std::isdigit(value[pos])) {
			note += value[pos] == '#' ? +1 : -1;
			++pos;
		}

		notes.push_back(note + 12 * GetNumber(value, pos));
	}

	return {notes, phrase_length};
}

} // namespace

MelodyParser::MelodyParser(const storage::Path& filename)
	: database_iterator_(storage::List<Phrase>(
				kMelodiesPath / filename, ParsePhraseFromString, '\n').begin()) {}

void MelodyParser::NextPhrase() {
	++database_iterator_;
	++pos_;
}

void MelodyParser::ParsePhrase() {
	phrase_ = *database_iterator_;
}

// Phrase MelodyParser::ParsePhraseAt(uint16_t pos) {
// 	Phrase phrase;
// 	uint8_t notes_count = melody_[pos];
//
//   for (uint8_t i = 0; i < notes_count; i++) {
//     phrase.notes.push_back(melody_[pos + i + 1]);
//   }
//   phrase.length = melody_[pos + notes_count + 1];
// 	return phrase;
// }

} // namespace synth
