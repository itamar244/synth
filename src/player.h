// Player basic polymorphic class, which implemented by all players.
// The players should inherit `Player` to share common `Play` function logic.
//
// Each player should implement all PLAYER_CALLBACKS,
// so they will be called for `Player`.
#pragma once

#include <Arduino.h>
#include "audio.h"
#include "phrase.h"

namespace synth {

class MelodyComparator;

#define PLAYER_CALLBACKS(PREFIX, POSTFIX)                                      \
	PREFIX void ParsePhrase() POSTFIX;                                           \
	PREFIX const Phrase::Tones& GetPhraseTones() const POSTFIX;                  \
	PREFIX bool ShouldChangeToNextPhrase() const POSTFIX;                        \
	PREFIX void NextPhrase() POSTFIX;                                            \
	PREFIX bool ShouldContinue() const POSTFIX;                                  \
	PREFIX void WhenFinished() POSTFIX;

// should be called in each subclass in the protected part
#define PLAYER_CALLBACKS_INHERIT PLAYER_CALLBACKS(, override)

struct Player {
public:
	virtual ~Player();
	bool Play(Audio* audio);
	// FIX: I know this is ugly, but arduino doesn't have dynamic_cast so I can't tell
	// if the instance is comparator or not. UGLY ESACPE HATCH
	virtual MelodyComparator* ToComparator() { return nullptr; }

protected:
	uint32_t prev_millis_ = millis();
	bool started_ = false, ended_ = false;


	PLAYER_CALLBACKS(virtual, = 0)
};

} // namespace synth
