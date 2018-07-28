#include <SFML/Graphics.hpp>
// #include "store.h"
#include "env.h"
#include "keyboard.h"
#include "sound.h"
#include "screen/screen.h"

// namespace serial = synth::serial;
// namespace sound = synth::sound;
// namespace store = synth::store;
//
using synth::Environment;
using synth::ListenToKeyboardInput;
using ScreenController = synth::screen::Controller;
// using Route = synth::screen::Route;


Environment env;
ScreenController screen_controller;

inline void Loop(sf::RenderWindow& window) {
	env.Tick();
	screen_controller.Paint(env, window);
	ListenToKeyboardInput(env);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		screen_controller.Touch(env, window, sf::Mouse::getPosition(window));
	} else if (screen_controller.is_touched()) {
		screen_controller.Touchend(env, window);
	}
}

int main() {
	// store::MaybeInit();

	sf::RenderWindow window(sf::VideoMode(500, 300), "Synth");

	window.setVerticalSyncEnabled(true);
	window.clear(sf::Color::Black);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				Loop(window);
			}
		}
	}

	for(;;);

	return 0;
}
