#include "screen/screen.h"
#include <TFT9341.h>
#include "env.h"
#include "screen/routes.h"

#define CASE_ROUTE_TYPES(V, ROUTE)                                             \
  case Route::k ## ROUTE:                                                      \
    V(ROUTE)                                                                   \
    break;

// create a switch-case statement with each possible route
#define SWITCH_ROUTE_TYPES(V)                                                  \
  switch (route_) {                                                            \
    WRAPPED_ROUTE_TYPES(CASE_ROUTE_TYPES, V)                                   \
  }

namespace synth {
namespace screen {

// fixing some weird inconsistencies with screen's touch
inline Point GetClickedPoint() {
  lcdtouch.readxy();
  const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();

  return {
    (WIDTH - x - 80) * 1.3,
    (y - 13) / 1.3,
  };
}

Controller::Controller()
  : route_(Route::kIndex) {}

void Controller::Paint(Environment& env) {
  if (!is_painted_) {
    is_painted_ = true;
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    Touchend(env);
#define V(ROUTE) buttons_ = RouteInit ## ROUTE();
    SWITCH_ROUTE_TYPES(V)
#undef V
  }
}

void Controller::Touch(Environment& env) {
  const Point point = GetClickedPoint();
	is_touched_ = true;

#define V(ROUTE) RouteTouch ## ROUTE(this, buttons_, env, point);
  SWITCH_ROUTE_TYPES(V)
#undef V
}

void Controller::Touchend(Environment& env) {
	is_touched_ = false;

	for (auto& button : buttons_) {
		if (button.is_pressed) {
			button.is_pressed = false;
		}
	}
}

}  // namespace screen
}  // namespace synth
