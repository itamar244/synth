#pragma once

#include "audio.h"
#include "phrase.h"

namespace synth {

struct Player;

#define PLAY_WRAPPER(PREV_DECLARATIONS)                                        \
	PREV_DECLARATIONS bool PlayWrapper(                                          \
			Audio* audio,                                                            \
			Player* player,                                                          \
			/* void */                                                               \
			const auto& eat_next,                                                    \
			/* Phrase::Tones& */                                                     \
			const auto& get_phrase_tones,                                            \
			/* bool */                                                               \
			const auto& should_change_to_next_phrase,                                \
			/* void */                                                               \
			const auto& next_phrase,                                                 \
			/* bool */                                                               \
			const auto& is_finished,                                                 \
			/* void */                                                               \
			const auto& when_finished)

struct Player {
protected:
	uint32_t prev_millis_ = millis();
	bool started_ = false;

	PLAY_WRAPPER(friend);
};

PLAY_WRAPPER() {
  if (is_finished()) return false;
  if (!player->started_) {
    eat_next();
		audio->AddTones(get_phrase_tones());
		player->prev_millis_ = millis();
    player->started_ = true;
  } else if (should_change_to_next_phrase()) {
  	audio->RemoveTones(get_phrase_tones());
    next_phrase();
    if (!is_finished()) {
      eat_next();
			audio->AddTones(get_phrase_tones());
			player->prev_millis_ = millis();
    } else {
			when_finished();
		}
  }
  return true;
}

#undef PLAY_WRAPPER

} // namespace synth
