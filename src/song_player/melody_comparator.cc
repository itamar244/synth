#include "song_player/melody_comparator.h"
#include "utils.h"

namespace synth {

void MelodyComparator::Init(Song song, uint16_t size) {
	SongPlayer::Init(song, size);
	grade_ = 0;
	compare_pos_ = 0;
	phrase_count_ = 0;
}

void MelodyComparator::AddPhraseToCompare(
		const PGMPhrase& phrase) {
	auto to_compare = ParsePhraseAt(compare_pos_);
	uint8_t correct_items = 0;

	for (auto tone : phrase.tones) {
		if (utils::HasItem(to_compare.tones, tone)) correct_items++;
	}
	grade_ += to_compare.tones.size() / float(correct_items);
}

} // namespace synth
