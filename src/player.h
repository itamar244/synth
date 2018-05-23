// Player basic class, which implemented by all players.
// The players should inherit `Player` to share common `Play` function logic.
//
// Each player should call `Player::Play` in its own `Play` function and
// provide the correct callbacks to `Player::Play`.
//
// The following callbacks should be provided, by this order:
//   - void                 eat_next()
//   - const Phrase::Tones& get_phrase_tones()
//   - bool                 should_change_to_next_phrase()
//   - void                 next_phrase()
//   - bool                 is_finished()
//   - void                 when_finished()
#pragma once

#include <Arduino.h>
#include "audio.h"
#include "phrase.h"

namespace synth {

struct Player {
protected:
	uint32_t prev_millis_ = millis();
	bool started_ = false;

	bool Play(
			Audio* audio,
			/* void */
			const auto& eat_next,
			/* Phrase::Tones& */
			const auto& get_phrase_tones,
			/* bool */
			const auto& should_change_to_next_phrase,
			/* void */
			const auto& next_phrase,
			/* bool */
			const auto& is_finished,
			/* void */
			const auto& when_finished) {
		if (is_finished()) return false;
		if (!started_) {
			eat_next();
			audio->AddTones(get_phrase_tones());
			prev_millis_ = millis();
			started_ = true;
		} else if (should_change_to_next_phrase()) {
			audio->RemoveTones(get_phrase_tones());
			next_phrase();
			if (!is_finished()) {
				eat_next();
				audio->AddTones(get_phrase_tones());
				prev_millis_ = millis();
			} else {
				when_finished();
			}
		}

		return true;
	}
};

} // namespace synth
