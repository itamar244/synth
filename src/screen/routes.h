/**
 * responsible for screen painting and touch responses.
 * RouteInit<ROUTE> and PageTouch<TYPE><ROUTE> are generated and are being used
 * in "screen/screen.cc".
 * each ROUTE is implemented in `screen/pages/ROUTE.cc`.
 */
#pragma once

#include <StandardCplusplus.h>
#include <cstddef> // included for <initializer_list>
#include <initializer_list>
#include <Arduino.h>
#include "env.h"
#include "screen/button.h"
#include "screen/screen.h"

#define ROUTE_TYPES(V)                                                         \
  V(Index)                                                                     \
  V(Menu)                                                                      \
  V(Keyboard)                                                                  \
  V(PracticePlayerList)                                                        \
  V(PracticePlayerPlaying)                                                     \
  V(Settings)

#define WRAPPED_ROUTE_TYPES(WRAPPER, V)                                        \
  WRAPPER(V, Index)                                                            \
  WRAPPER(V, Menu)                                                             \
  WRAPPER(V, Keyboard)                                                         \
  WRAPPER(V, PracticePlayerList)                                               \
  WRAPPER(V, PracticePlayerPlaying)                                            \
  WRAPPER(V, Settings)

#define ROUTE_INIT(ROUTE)                                                      \
  std::vector<Button> RouteInit ## ROUTE()

#define ROUTE_TOUCH(ROUTE)                                                     \
  void RouteTouch ## ROUTE(                                                    \
    Controller* controller, std::vector<Button>& buttons,                      \
    Environment& env, const Point& point)

#define ROUTE_TOUCHEND(ROUTE)                                                  \
  void RouteTouchend ## ROUTE(                                                 \
    std::vector<Button>& buttons, Environment& env)

namespace synth {
namespace screen {

enum class Route {
#define V(ROUTE) k ## ROUTE,
	ROUTE_TYPES(V)
#undef V
};

// pages definition's utilities
void ClearButtonClicks(std::vector<Button>& buttons);

template<class Cb>
void IterateThroughPressedButtons(
		std::vector<Button>& buttons,
		const Point& point,
		const Cb& callback) {
	for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
				callback(i);
      }
      return;
    }
	}
}

template<class Cb>
void IteratethroughUnPressedButtons(
		std::vector<Button>& buttons,
		const Cb& callback) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.is_pressed) {
      button.is_pressed = false;
      callback(i);
    }
  }
}

std::vector<Button> PaintMenu(
		const std::initializer_list<const char*>& names);

#define V(ROUTE)                                                               \
  ROUTE_INIT(ROUTE);                                                           \
  ROUTE_TOUCH(ROUTE);                                                          \
  ROUTE_TOUCHEND(ROUTE);
  ROUTE_TYPES(V)
#undef V

} // namespace screen
} // namespace synth
