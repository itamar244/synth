#include "melody_player/melody_comparator.h"
#include <algorithm>
#include <utility>
#include <atic/iterables.h>

namespace synth {

using melo::Phrase;
using NoteList = Audio::NoteList;

inline uint8_t CountNoteListInPhrase(
		const NoteList& notes, const Phrase& phrase) {
	return std::count_if(
		notes.begin(), notes.end(),
		[&phrase](auto note) {
			return atic::HasItem(phrase.notes, note);
		});
}

MelodyComparator::MelodyComparator(std::ifstream& file)
		: MelodyPlayer(file), grade_(0), max_grade_(0) {
	InitFlags();
}

bool MelodyComparator::NextSection() {
	if (walker_.HasNextItem()) {
		if (walker_.pos() > 0) {
			InitFlags();
			cur_section_++;
		}
		return true;
	}
	return false;
}

// prev_millis_ is being used only for extremely short phrases to guard
// against tiny user mistakes
void MelodyComparator::AddNotesToCompare(const NoteList& notes) {
	// if user played more phrases than needed
	// than it will decrease five precents from grade for each phrase
	if (!ShouldContinue()) {
		grade_ *= 95 / 100;
	} else if (!started_) {
		started_ = true;
		UpdateTime();
	} else {
		uint32_t phrase_millis = GetUpdateTime();

		if (phrase_millis > 10) {
			// skeeping over comparing empty phrases
			for (;;) {
				ParsePhrase();
				if (phrase_.notes.empty()) {
					NextPhrase();
				} else {
					break;
				}
			}

			if (notes.size() > 0) {
				grade_ += CountNoteListInPhrase(notes, phrase_);
				max_grade_ += phrase_.notes.size();
				NextPhrase();
			}
		}
	}
}

bool MelodyComparator::ShouldContinue() const {
	return cur_section_ == walker_.pos();
}

void MelodyComparator::WhenFinished() {
	started_ = false;
}

} // namespace synth
