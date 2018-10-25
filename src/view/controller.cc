#include "view/controller.h"
#include <iostream>
#include "view/routes.h"

#define CASE_ROUTE_TYPES(V, ROUTE)                                             \
	case Route::k ## ROUTE:                                                      \
		V(ROUTE)                                                                   \
		break;

// create a switch-case statement with each possible route
#define SWITCH_ROUTE_TYPES(V)                                                  \
	switch (route_) {                                                            \
		WRAPPED_ROUTE_TYPES(CASE_ROUTE_TYPES, V)                                   \
	}

namespace synth::view {

Controller::Controller()
		: route_(Route::kIndex) {}

void Controller::Paint(Environment& env, sf::RenderWindow& window) {
	if (!is_painted_) {
		is_painted_ = true;
		window.clear(sf::Color::Black);

		Touchend(env, window);
#define V(ROUTE) buttons_ = RouteInit ## ROUTE(window);
		SWITCH_ROUTE_TYPES(V)
#undef V

		window.display();
	}
}

void Controller::Touch(
		Environment& env, sf::RenderWindow& window, sf::Vector2i point_vec) {
	const Point point = { point_vec.x, point_vec.y };
	is_touched_ = true;

#define V(ROUTE) RouteTouch ## ROUTE({ this, window, buttons_, env, point });
	SWITCH_ROUTE_TYPES(V)
#undef V
}

void Controller::Touchend(Environment& env, sf::RenderWindow& window) {
	is_touched_ = false;

	for (auto& button : buttons_) {
		if (button.is_pressed) {
			button.is_pressed = false;
		}
	}
}

} // namespace synth::view
