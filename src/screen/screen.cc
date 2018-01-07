#include "screen/screen.h"
#include <TFT9341.h>
#include "env.h"
#include "screen/pages.h"

#define CASE_PAGE_TYPES(V, PAGE)                                               \
  case Page::k ## PAGE:                                                        \
    V(PAGE)                                                                    \
    break;

#define SWITCH_PAGE_TYPES(V)                                                   \
  switch (page_) {                                                             \
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

Controller::Controller()
  : page_(Page::kIndex) {}

void Controller::Paint(Environment& env) {
  if (!is_painted_) {
    is_painted_ = true;
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    Touchend(env);
#define V(PAGE) buttons_ = PagePaint ## PAGE();
    SWITCH_PAGE_TYPES(V)
#undef V
  }
}

void Controller::Touch(Environment& env) {
  const Point point = GetClickedPoint();

#define V(PAGE) PageTouch ## PAGE(this, buttons_, env, point);
  SWITCH_PAGE_TYPES(V)
#undef V
}

void Controller::Touchend(Environment& env) {
#define V(PAGE) PageTouchend ## PAGE(buttons_, env);
  SWITCH_PAGE_TYPES(V)
#undef V
}

}  // namespace screen
}  // namespace synth
