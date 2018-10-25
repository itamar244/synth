#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "store.h"
#include "env.h"
#include "keyboard.h"
#include "view/controller.h"

namespace store = synth::store;

using synth::Environment;
using synth::ListenToKeyboardInput;
using ViewController = synth::view::Controller;

Environment env;
ViewController view_controller;

void TickLoop() {
	for (;;) {
		env.Tick();
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

inline void Loop(sf::RenderWindow& window, sf::Event& event) {
	view_controller.Paint(env, window);
	if (event.type == sf::Event::KeyPressed ||
			event.type == sf::Event::KeyReleased) {
		ListenToKeyboardInput(env);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		view_controller.Touch(env, window, sf::Mouse::getPosition(window));
	} else if (view_controller.is_touched()) {
		view_controller.Touchend(env, window);
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
