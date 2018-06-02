#include "player.h"
#include "serial_communication.h"

namespace synth {

Player::~Player() {}

#define AUDIO(PHASE) audio->PHASE ## Tones(GetPhraseTones())

bool Player::Play(Audio* audio) {
	if (ended_) {
		return false;
	}

	if (!started_) {
		ParsePhrase();
		AUDIO(Add);
		UpdateTime();
		started_ = true;
	} else if (ShouldChangeToNextPhrase()) {
		AUDIO(Remove);
		NextPhrase();

		if (ShouldContinue()) {
			ParsePhrase();
			AUDIO(Add);
			UpdateTime();
		} else {
			ended_ = true;
			WhenFinished();
		}
	}

	return true;
}

} // namespace synth
