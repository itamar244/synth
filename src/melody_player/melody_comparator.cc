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
		, max_grade_(0)
		, grade_(0) {
	InitFlags();
}

bool MelodyComparator::NextSection() {
	if (cur_section_ < sections_->size() - 1) {
		if (pos() > 0) {
			cur_section_++;
			InitFlags();
		}
		return true;
	}
	return false;
}

void MelodyComparator::AddTonesToCompare(const ToneList& tones) {
	// if user played more phrases than needed
	// than it will decrease five precents from grade for each phrase
	if (!compare_pos_ < pos()) {
		grade_ *= 95 / 100;
	} else if (!started_) {
		started_ = true;
		prev_millis_ = millis();
	} else {
		// current user phrase length in milliseconds
		uint16_t phrase_length = millis() - prev_millis_;
		Phrase to_compare = ParsePhraseAt(compare_pos_);

		if (to_compare.tones.size() == 0) {
			if (tones.size() == 0) {
				grade_++;
				max_grade_++;
				compare_pos_ += 2;
			}
		} else if (tones.size() > 0) {
			grade_ += CountToneListInPhrase(tones, to_compare);
			max_grade_ += to_compare.tones.size();
			compare_pos_ += to_compare.tones.size() + 2;
		}

		prev_millis_ += phrase_length;
	}
}

void MelodyComparator::EatNext() {
	MelodyPlayer::EatNext();
	section_time_ += phrase().length;
}

void MelodyComparator::NextPhrase() {}

bool MelodyComparator::ShouldContinue() const {
	return MelodyPlayer::ShouldContinue() && section_time_ / 32 < sections_->at(cur_section_);
}

void MelodyComparator::WhenFinished() {
	started_ = false;
}

} // namespace synth
