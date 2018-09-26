#include "screen/routes.h"
#include <string>
#include <SFML/Graphics.hpp>

namespace synth {
namespace screen {

inline void PaintGrade(sf::RenderWindow& window, float grade) {
	uint16_t x = window.getSize().x / 2 + 50;
	uint16_t y = window.getSize().y / 2 - 40;

	window.draw(CreateRectShape({x, y, 100, 40}, sf::Color::White));
	window.draw(CreateText(std::to_string(grade), x + 20, y + 15));
}

ROUTE_INIT(PracticePlayerPlaying) {
	return PaintMenu(window, {
		"Back",
		"Start",
		"Commit",
	});
}

ROUTE_TOUCH(PracticePlayerPlaying) {
	state.IteratePressedButtons([&state](uint8_t index) {
		switch (index) {
			case 0: // Back
				state.controller->set_route(Route::kPracticePlayerList);
				state.env.DeletePlayer();
				break;
			case 1: // Start
				state.env.StartPlaying();
				break;
			case 2: // Commit
				auto status = state.env.ComparatorNextSection();
				if (!status.first) {
					PaintGrade(state.window, status.second);
				}
				break;
		}
	});
}

} // namespace screen
} // namespace synth
