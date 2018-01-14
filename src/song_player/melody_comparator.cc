#include "song_player/melody_comparator.h"
#include <StandardCplusplus.h>
#include <algorithm>
#include <Arduino.h>
#include "audio.h"

namespace synth {

using PGMPhrase = PGMSongParser::PGMPhrase;

const uint8_t kTime32nd = 60;

inline uint8_t CountToneListInPhrase(
		const Audio::ToneList& tones, const PGMPhrase& phrase) {
	return std::count_if(
		tones.begin(), tones.end(),
		[&phrase](Audio::Tone tone) {
			return utils::HasItem(phrase.tones, tone);
		});
}

MelodyComparator::MelodyComparator(const SongContainer& container)
	: PGMSongParser(container)
	, sections_(container.sections)
	, section_time_(0)
	, cur_section_(0)
	, compare_pos_(0)
	, max_grade_(0)
	, grade_(0) {
	InitFlags(false);
}

bool MelodyComparator::NextSection() {
	if (cur_section_ < sections_.size() - 1) {
		if (pos_ > 0) {
			cur_section_++;
			section_time_ = 0;
			InitFlags(false);
		}
		return true;
	}
	return false;
}

void MelodyComparator::AddTonesToCompare(const Audio::ToneList& tones) {
	// if user played more phrases than needed
	if (!ShouldCompare()) {
		grade_ -= grade_ * 5 / 100;
	} else if (!started_section_) {
		started_section_ = true;
		prev_millis_ = millis();
	} else {
		// current user phrase length in milliseconds
		uint16_t phrase_length = millis() - prev_millis_;
		PGMPhrase to_compare = ParsePhraseAt(compare_pos_);
		if (to_compare.tones.size() == 0) {
			if (tones.size() == 0) {
				grade_++;
				max_grade_++;
				compare_pos_ += 2;
			}
		} else if (phrase_length > kTime32nd * 3 || tones.size() > 0) {
			uint8_t correct_items = CountToneListInPhrase(tones, to_compare);
			if (correct_items > 0) {
				grade_ += to_compare.tones.size() / float(correct_items);
			}
			max_grade_++;
			compare_pos_ += to_compare.tones.size() + 2;
		}

		// max_grade_++;
		prev_millis_ += phrase_length;
	}
}


bool MelodyComparator::Play(Audio* audio) {
  if (ended_section_) return false;

  if (!started_section_) {
    PlayNext(audio);
    started_section_ = true;
  } else if (millis() - prev_millis_ >= phrase_.length * kTime32nd) {
    audio->RemoveTones(phrase_.tones);

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
