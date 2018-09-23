#include "keyboard.h"
#include <iostream>
#include <vector>
#include "audio.h"

using kb = sf::Keyboard;

namespace synth {

namespace {

const std::vector<kb::Key> kNotes({
	kb::Z, kb::S, kb::X, kb::D, kb::C, kb::V,	kb::G, kb::B,	kb::H, kb::N,	kb::J, kb::M,
	kb::Q, kb::Num2, kb::W, kb::Num3, kb::E, kb::R, kb::Num5, kb::T, kb::Num6, kb::Y, kb::Num7, kb::U, kb::I
});

std::vector<bool> isKeyPressed(kNotes.size(), false);

inline void ListenToNotesKeys(Environment& env) {
	for (uint8_t i = 0; i < isKeyPressed.size(); i++) {
		if (kb::isKeyPressed(kNotes[i])) {
			if (!isKeyPressed[i]) {
				env.AddNoteWithOctave(i);
				isKeyPressed[i] = true;
			}
		} else {
			if (isKeyPressed[i]) {
				env.RemoveNoteWithOctave(i);
				isKeyPressed[i] = false;
			}
		}
	}
}

inline void ListenToSpecialKeys(Environment& env) {
	if (kb::isKeyPressed(kb::Dash)) {
		env.DecrementOctave();
	} else if (kb::isKeyPressed(kb::Equal)) {
		env.IncrementOctave();
	} else if (kb::isKeyPressed(kb::Num9)) {
		env.StartRecording();
	} else if (kb::isKeyPressed(kb::Num0)) {
		env.StopRecording();
	}
}

} // namespace

void ListenToKeyboardInput(Environment& env) {
	ListenToNotesKeys(env);
	if (env.audio()->current_notes().empty()) {
		 ListenToSpecialKeys(env);
	}
}

} // namespace synth
