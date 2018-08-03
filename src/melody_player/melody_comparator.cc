#include "melody_comparator.h"
#include <algorithm>
#include <atic/iterables.h>
#include "../phrase.h"

namespace synth {

using Note = Audio::Note;
using NoteList = Audio::NoteList;

inline uint8_t CountNoteListInPhrase(
		const NoteList& notes, const Phrase& phrase) {
	return std::count_if(
		notes.begin(), notes.end(),
		[&phrase](Note note) {
			return atic::HasItem(phrase.notes, note);
		});
}

MelodyComparator::MelodyComparator(const MelodyContainer& container)
		: MelodyPlayer(container)
		, sections_(container.sections)
		, cur_section_(0)
		, compare_pos_(0)
		, grade_(0)
		, max_grade_(0) {
	InitFlags();
}

bool MelodyComparator::NextSection() {
	if (cur_section_ < sections_.size() - 1) {
		if (pos() > 0) {
			compare_pos_ = pos();
			cur_section_++;
			InitFlags();
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
	if (compare_pos_ >= pos()) {
		grade_ *= 95 / 100;
	} else if (!started_) {
		started_ = true;
		UpdateTime();
	} else {
		uint32_t phrase_millis = GetUpdateTime();


		if (phrase_millis > 10) {
			Phrase to_compare;

			// skeeping over comparing empty phrases
			for (;;) {
				to_compare = ParsePhraseAt(compare_pos_);
				if (to_compare.Size() == 0) {
					compare_pos_ += 2;
				} else {
					break;
				}
			}

			if (notes.size() > 0) {
				grade_ += CountNoteListInPhrase(notes, to_compare);
				max_grade_ += to_compare.Size();
				compare_pos_ += to_compare.Size() + 2;
			}
		}
	}
}

void MelodyComparator::ParsePhrase() {
	MelodyPlayer::ParsePhrase();
	section_time_ += phrase().length;
}

bool MelodyComparator::ShouldContinue() const {
	return MelodyPlayer::ShouldContinue()
			&& section_time_ / 32 < sections_[cur_section_];
}

void MelodyComparator::WhenFinished() {
	started_ = false;
}

} // namespace synth
