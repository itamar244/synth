#include "keyboard.h"
#include <iostream>
#include <vector>
#include "audio.h"

namespace synth {

namespace {

const std::vector<sf::Keyboard::Key> kNotes({
	sf::Keyboard::Z,
	sf::Keyboard::S,
	sf::Keyboard::X,
	sf::Keyboard::D,
	sf::Keyboard::C,
	sf::Keyboard::V,
	sf::Keyboard::G,
	sf::Keyboard::B,
	sf::Keyboard::H,
	sf::Keyboard::N,
	sf::Keyboard::J,
	sf::Keyboard::M,

  sf::Keyboard::Q,
	sf::Keyboard::Num2,
	sf::Keyboard::W,
	sf::Keyboard::Num3,
	sf::Keyboard::E,
	sf::Keyboard::R,
	sf::Keyboard::Num5,
	sf::Keyboard::T,
	sf::Keyboard::Num6,
	sf::Keyboard::Y,
	sf::Keyboard::Num7,
	sf::Keyboard::U,
	sf::Keyboard::I,
});

std::vector<bool> isKeyPressed(kNotes.size(), false);
} // namespace

void ListenToKeyboardInput(Environment& env) {
	for (uint8_t i = 0; i < isKeyPressed.size(); i++) {
		if (sf::Keyboard::isKeyPressed(kNotes[i])) {
			std::cout << "asdc" << '\n';
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

} // namespace synth
