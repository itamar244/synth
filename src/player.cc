#include "player.h"
#include "serial_communication.h"

namespace synth {

Player::~Player() {}

#define AUDIO(PHASE) audio->PHASE ## Tones(GetPhraseTones())

bool Player::Play(Audio* audio) {
	if (!ShouldContinue()) {
		return false;
	}

	if (!started_) {
		EatNext();
		AUDIO(Add);
		prev_millis_ = millis();
		started_ = true;
	} else if (ShouldChangeToNextPhrase()) {
		AUDIO(Remove);
		NextPhrase();

		if (ShouldContinue()) {
			EatNext();
			AUDIO(Add);
			prev_millis_ = millis();
		} else {
			WhenFinished();
		}
	}

	return true;
}

} // namespace synth
