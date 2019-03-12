#include <SFML/Graphics.hpp>
#include "view/elements.h"
#include "view/routes.h"

namespace synth {
namespace view {

ROUTE_INIT(Index) {
	const auto dimensions = window.getSize();
	const int width = 120, height = 40;
	const float x = dimensions.x / 2 - width / 2;
	const float y = dimensions.y / 2 - height / 2;
	Button button = { x, y, width, height };

	window.draw(TextElement("Itamar Yatom Project", x - 40, y - 30));
	window.draw(ButtonElement("Continue", sf::Color::Blue, x, y));

	return {button};
}

ROUTE_TOUCH(Index) {
	if (state.buttons[0].IsTapped(state.point)) {
		state.controller->set_route(Route::kMenu);
	}
}

} // namespace view
} // namespace synth
