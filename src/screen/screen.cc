#include "screen/screen.h"
#include <TFT9341.h>
#include "env.h"
#include "screen/pages.h"

#define CASE_PAGE_TYPES(V, PAGE)                                               \
  case Page::PAGE:                                                             \
    V(PAGE)                                                                    \
    break;

#define SWITCH_PAGE_TYPES(V)                                                   \
  switch (env.get_page()) {                                                    \
    WRAPPED_PAGE_TYPES(CASE_PAGE_TYPES, V)                                     \
  }

namespace synth {
namespace screen {

inline Point get_clicked_point() {
  lcdtouch.readxy();
  const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();

  return {
    (WIDTH - x - 80) * 1.3,
    (y - 13) / 1.3,
  };
}

void Controller::paint(Environment& env) {
  if (env.should_paint_screen()) {
    env.screen_painted();
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

#define V(PAGE) buttons_ = page_paint_ ## PAGE();
  SWITCH_PAGE_TYPES(V)
#undef V
  }
}

void Controller::touch(Environment& env) {
  const Point point = get_clicked_point();

#define V(PAGE) page_touch_ ## PAGE(buttons_, env, point);
  SWITCH_PAGE_TYPES(V)
#undef V
}

void Controller::touchend(Environment& env) {
#define V(PAGE) page_touchend_ ## PAGE(buttons_, env);
  SWITCH_PAGE_TYPES(V)
#undef V
}

}  // namespace screen
}  // namespace synth
