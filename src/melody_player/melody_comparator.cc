#include "melody_player/melody_comparator.h"
#include <StandardCplusplus.h>
#include <algorithm>
#include <Arduino.h>
#include "phrase.h"

namespace synth {

using Tone = Audio::Tone;
using ToneList = Audio::ToneList;

inline uint8_t CountToneListInPhrase(
		const ToneList& tones, const Phrase& phrase) {
	return std::count_if(
		tones.begin(), tones.end(),
		[&phrase](Tone tone) {
			return utils::HasItem(phrase.tones, tone);
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
	if (cur_section_ < sections_->size() - 1) {
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
void MelodyComparator::AddTonesToCompare(const ToneList& tones) {
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

			if (tones.size() > 0) {
				grade_ += CountToneListInPhrase(tones, to_compare);
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
			&& section_time_ / 32 < sections_->at(cur_section_);
}

void MelodyComparator::WhenFinished() {
	started_ = false;
}

} // namespace synth
