// MelodyComparator's roles are:
//   - play the sections of a melody.
//   - compare a given phrases to the melody.
//   - calculate a grade that represents the given phrases simillarity to the melody.
#include "melody_player/melody_comparator.h"
#include <StandardCplusplus.h>
#include <algorithm>
#include <Arduino.h>
#include "audio.h"
#include "empty.h"
#include "phrase.h"

namespace synth {

using Tone = Audio::Tone;
using ToneList = Audio::ToneList;

const uint8_t kTime32nd = 60;

inline uint8_t CountToneListInPhrase(
		const ToneList& tones, const Phrase& phrase) {
	return std::count_if(
		tones.begin(), tones.end(),
		[&phrase](Tone tone) {
			return utils::HasItem(phrase.tones, tone);
		});
}

MelodyComparator::MelodyComparator(const MelodyContainer& container)
		: MelodyParser(container)
		, sections_(container.sections)
		, cur_section_(0)
		, compare_pos_(0)
		, max_grade_(0)
		, grade_(0) {
	InitFlags();
}

bool MelodyComparator::NextSection() {
	if (cur_section_ < sections_.size() - 1) {
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
	// than it will decrease five precents from grade for each note
	if (!ShouldCompare()) {
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
		} else if (phrase_length > kTime32nd * 3 || tones.size() > 0) {
			grade_ += CountToneListInPhrase(tones, to_compare);
			max_grade_ += to_compare.tones.size();
			compare_pos_ += to_compare.tones.size() + 2;
		}

		prev_millis_ += phrase_length;
	}
}

bool MelodyComparator::Play(Audio* audio) {
	return Player::Play(
			audio,
			[this]() -> void { EatNext(); },
			[this]() -> const Phrase::Tones& { return phrase_tones(); },
			[this]() -> bool { return millis() - prev_millis_ >= phrase().length * kTime32nd; },
			empty::callback,
			[this]() -> bool { return (
				ended_
				|| (HasNextPhrase() && section_time_ / 32 < sections_[cur_section_])
			); },
			[this]() -> void {
				started_ = false;
				ended_ = comparing_ = true;
			});
}

} // namespace synth
