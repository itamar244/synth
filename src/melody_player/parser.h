#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>
#include "../storage/list.h"
#include "../audio.h"
#include "../phrase.h"

namespace synth {

class MelodyParser {
public:
  MelodyParser(const storage::Path& filename);

	inline bool HasNextPhrase() const {
		return bool(database_iterator_);
	}
	inline const Audio::NoteList& phrase_notes() const {
		return phrase_.notes;
	}

	inline const Phrase& phrase() const { return phrase_; }
	inline const uint16_t pos() const { return pos_; }

	void ParsePhrase();
  void NextPhrase();
  // Phrase ParsePhraseAt(uint16_t pos);

private:
  storage::List<Phrase>::iterator database_iterator_;
	Phrase phrase_;
	std::size_t pos_;
};

} // namespace synth
