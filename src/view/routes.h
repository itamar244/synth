// Responsible for view's painting and touch responses.
// RouteInit<ROUTE> and PageTouch<TYPE><ROUTE> are generated and are being used
// in "view/view.cc".
// each ROUTE is implemented in `view/pages/ROUTE.cc`.
#pragma once

#include <initializer_list>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "env.h"
#include "view/button.h"
#include "view/controller.h"

#define ROUTE_TYPES(V)                                                         \
	V(Index)                                                                     \
	V(Menu)                                                                      \
	V(Player)                                                                    \
	V(PracticePlayerList)                                                        \
	V(PracticePlayerPlaying)                                                     \
	V(RecordsPlayer)                                                             \
	/*V(Settings)*/

#define WRAPPED_ROUTE_TYPES(WRAPPER, V)                                        \
	WRAPPER(V, Index)                                                            \
	WRAPPER(V, Menu)                                                             \
	WRAPPER(V, Player)                                                           \
	WRAPPER(V, PracticePlayerList)                                               \
	WRAPPER(V, PracticePlayerPlaying)                                            \
	WRAPPER(V, RecordsPlayer)                                                    \
	/*WRAPPER(V, Settings)*/

namespace synth::view {

enum class Route {
#define V(ROUTE) k ## ROUTE,
	ROUTE_TYPES(V)
#undef V
};

struct RouteState {
	Controller* controller;
	sf::RenderWindow& window;
	std::vector<Button>& buttons;
	Environment& env;
	const Point& point;

	template<class Cb>
	inline void IteratePressedButtons(const Cb& callback) {
		Button::IteratePressed(buttons, point, callback);
	}
};

#define ROUTE_INIT(ROUTE)                                                      \
	std::vector<Button> RouteInit ## ROUTE(sf::RenderWindow& window)

#define ROUTE_TOUCH(ROUTE)                                                     \
	void RouteTouch ## ROUTE(RouteState state)

#define V(ROUTE)                                                               \
	ROUTE_INIT(ROUTE);                                                           \
	ROUTE_TOUCH(ROUTE);
	ROUTE_TYPES(V)
#undef V

using PaintMenuNames = std::initializer_list<const std::string>;

/*
 * Paints a menu with buttons for each name, and a `back` button.
 * Returns the buttons representing the names with the same order,
 * and another button in the end representing the `back` button
 *
 * Each button is beneeth the previuos one's with nice padding and margin.
 */
std::vector<Button> PaintMenu(
		sf::RenderWindow& window, const PaintMenuNames& names);
std::vector<Button> PaintMenu(
		sf::RenderWindow& window,
		const std::initializer_list<PaintMenuNames>& names);

/*
 * Paints a keyboard with buttons for each name, and a `back` button.
 * Returns the buttons representing the names with the same order,
 * and another button in the end representing the `back` button.
 *
 * Each line contains three buttons, up to 11 buttons total.
 */
std::vector<Button> PaintKeyboard(
		sf::RenderWindow& window, const PaintMenuNames&);

} // namespace synth::view
