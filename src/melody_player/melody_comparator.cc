// MelodyComparator's roles are:
//   - play the sections of a melody.
//   - compare a given phrases to the melody.
//   - calculate a grade that represents the given phrases simillarity to the melody.
#include "melody_player/melody_comparator.h"
#include <StandardCplusplus.h>
#include <algorithm>
#include <Arduino.h>
#include "audio.h"

namespace synth {

using Phrase = MelodyParser::Phrase;
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
	} else if (!started_section_) {
		started_section_ = true;
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
  if (ended_section_) return false;

  if (!started_section_) {
    PlayNext(audio);
    started_section_ = true;
  } else if (millis() - prev_millis_ >= phrase().length * kTime32nd) {
    audio->RemoveTones(phrase().tones);

    if (HasNextPhrase() && section_time_ / 32 < sections_[cur_section_]) {
      PlayNext(audio);
    } else {
			started_section_ = false;
			ended_section_ = comparing_ = true;
		}
  }
  return true;
}

} // namespace synth
