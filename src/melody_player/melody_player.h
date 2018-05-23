#pragma once

#include "melody_player/parser.h"
#include "player.h"

namespace synth {

class MelodyPlayer : public Player, public MelodyParser {
public:
	inline MelodyPlayer(const MelodyContainer& container)
		: MelodyParser(container)
		, speed_(container.speed) {}

protected:
	float speed_;
	PLAYER_CALLBACKS_INHERIT
};

} // namespace synth
