// Responsible for screen's painting and touch responses.
// RouteInit<ROUTE> and PageTouch<TYPE><ROUTE> are generated and are being used
// in "screen/screen.cc".
// each ROUTE is implemented in `screen/pages/ROUTE.cc`.
#pragma once

#include <StandardCplusplus.h>
#include <cstddef> // included for <initializer_list>
#include <initializer_list>
#include <vector>
#include "env.h"
#include "screen/button.h"
#include "screen/screen.h"

#define ROUTE_TYPES(V)                                                         \
  V(Index)                                                                     \
  V(Menu)                                                                      \
  V(Player)                                                                    \
  V(PracticePlayerList)                                                        \
  V(PracticePlayerPlaying)                                                     \
  V(RecordsPlayer)                                                             \
  V(Recorder)                                                                  \
  V(Settings)

#define WRAPPED_ROUTE_TYPES(WRAPPER, V)                                        \
  WRAPPER(V, Index)                                                            \
  WRAPPER(V, Menu)                                                             \
  WRAPPER(V, Player)                                                       \
  WRAPPER(V, PracticePlayerList)                                               \
  WRAPPER(V, PracticePlayerPlaying)                                            \
  WRAPPER(V, RecordsPlayer)                                                    \
  WRAPPER(V, Recorder)                                                         \
  WRAPPER(V, Settings)

#define ROUTE_INIT(ROUTE)                                                      \
  std::vector<Button> RouteInit ## ROUTE()

#define ROUTE_TOUCH(ROUTE)                                                     \
  void RouteTouch ## ROUTE(                                                    \
    Controller* controller, std::vector<Button>& buttons,                      \
    Environment& env, const Point& point)

namespace synth {
namespace screen {

enum class Route {
#define V(ROUTE) k ## ROUTE,
	ROUTE_TYPES(V)
#undef V
};

#define V(ROUTE)                                                               \
  ROUTE_INIT(ROUTE);                                                           \
  ROUTE_TOUCH(ROUTE);
  ROUTE_TYPES(V)
#undef V

using PaintMenuNames = std::initializer_list<const char*>;
/*
 * Paints a menu with buttons for each name, and a `back` button.
 * Returns the buttons representing the names with the same order,
 * and another button in the end representing the `back` button
 *
 * Each button is beneeth the previuos one's with nice padding and margin.
 */
std::vector<Button> PaintMenu(const PaintMenuNames& names);
std::vector<Button> PaintMenu(
		const std::initializer_list<PaintMenuNames>& names);

/*
 * Paints a keyboard with buttons for each name, and a `back` button.
 * Returns the buttons representing the names with the same order,
 * and another button in the end representing the `back` button.
 *
 * Each line contains three buttons, up to 11 buttons total.
 */
std::vector<Button> PaintKeyboard(
		const char* names[], uint16_t size);

} // namespace screen
} // namespace synth
