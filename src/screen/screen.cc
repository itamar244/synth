#include "screen/screen.h"
#include <TFT9341.h>
#include "env.h"
#include "screen/pages.h"

#define CASE_PAGE_TYPES(V, PAGE)                                               \
  case Page::PAGE:                                                             \
    V(PAGE)                                                                    \
    break;

#define SWITCH_PAGE_TYPES(V)                                                   \
  switch (env.page()) {                                                        \
    WRAPPED_PAGE_TYPES(CASE_PAGE_TYPES, V)                                     \
  }

namespace synth {
namespace screen {

inline Point GetClickedPoint() {
  lcdtouch.readxy();
  const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();

  return {
    (WIDTH - x - 80) * 1.3,
    (y - 13) / 1.3,
  };
}

void Controller::Paint(Environment& env) {
  if (env.ShouldPaintScreen()) {
    env.ScreenPainted();
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

#define V(PAGE) buttons_ = PagePaint_ ## PAGE();
  SWITCH_PAGE_TYPES(V)
#undef V
  }
}

void Controller::Touch(Environment& env) {
  const Point point = GetClickedPoint();

#define V(PAGE) PageTouch_ ## PAGE(buttons_, env, point);
  SWITCH_PAGE_TYPES(V)
#undef V
}

void Controller::Touchend(Environment& env) {
#define V(PAGE) PageTouchend_ ## PAGE(buttons_, env);
  SWITCH_PAGE_TYPES(V)
#undef V
}

}  // namespace screen
}  // namespace synth
