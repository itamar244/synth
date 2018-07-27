#include <SFML/Graphics.hpp>
#include "../routes.h"

namespace synth {
namespace screen {

ROUTE_INIT(Index) {
	const auto dimensions = window.getSize();
	const int width = 120, height = 40;
	const float x = dimensions.x / 2 - width / 2;
	const float y = dimensions.y / 2 - height / 2;
	Button button = { x, y, width, height };

	window.draw(CreateText("Itamar Yatom Project", x - 40, y - 30));
	window.draw(CreateRectShape(button, sf::Color::Blue));
	window.draw(CreateText("Continue", x + 15, y + 10));

	return {button};
}

ROUTE_TOUCH(Index) {
	if (buttons[0].IsTapped(point)) {
		controller->set_route(Route::kMenu);
	}
}

} // namespace screen
} // namespace synth
