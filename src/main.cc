#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "store.h"
#include "env.h"
#include "keyboard.h"
#include "screen/screen.h"

namespace store = synth::store;

using synth::Environment;
using synth::ListenToKeyboardInput;
using ScreenController = synth::screen::Controller;

Environment env;
ScreenController screen_controller;

void TickLoop() {
	for (;;) {
		env.Tick();
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

inline void Loop(sf::RenderWindow& window, sf::Event& event) {
	screen_controller.Paint(env, window);
	if (event.type == sf::Event::KeyPressed ||
			event.type == sf::Event::KeyReleased) {
		ListenToKeyboardInput(env);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		screen_controller.Touch(env, window, sf::Mouse::getPosition(window));
	} else if (screen_controller.is_touched()) {
		screen_controller.Touchend(env, window);
	}
}

int main(int argc, char const *argv[]) {
	store::MaybeInit();

	sf::RenderWindow window(sf::VideoMode(500, 300), "Synth", sf::Style::None);

	window.setVerticalSyncEnabled(true);
	window.clear(sf::Color::Black);

	std::thread tickerLoop(TickLoop);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed) {
				window.close();
				tickerLoop.detach();
			} else {
				Loop(window, event);
			}
		}
	}

	return 0;
}
