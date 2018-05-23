#pragma once

#include "melody_player/parser.h"
#include "player.h"

namespace synth {

class MelodyPlayer : public Player, public MelodyParser {
public:
	inline MelodyPlayer(const MelodyContainer& container)
		: MelodyParser(container) {}

protected:
	PLAYER_CALLBACKS_INHERIT
};

} // namespace synth
