// MelodyPlayer implements both Player And MelodyParser for parsing
// progmem melodies from `synth::melodies` and play them
#pragma once

#include "./parser.h"
#include "../player.h"
#include "../storage/fs.h"

namespace synth {

class MelodyPlayer : public Player, public MelodyParser {
public:
	MelodyPlayer(const storage::Path& path)
			: MelodyParser(path) {}

protected:
	PLAYER_CALLBACKS_INHERIT
};

} // namespace synth
