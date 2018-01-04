#include "screen/screen.h"
#include <TFT9341.h>
#include "app-state.h"
#include "screen/pages.h"

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

void Controller::paint(AppState& state) {
  if (state.should_paint_screen()) {
    state.screen_painted();
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    switch (state.get_page()) {
#define V(page_name)                                                           \
      case Page::page_name:                                                    \
        buttons_ = screen_ ## page_name();                                     \
        break;
      PAGE_TYPES(V)
#undef V
    }
  }
}

void Controller::touch(AppState& state) {
  const Point point = get_clicked_point();
  switch (state.get_page()) {
#define V(page_name)                                                           \
    case Page::page_name:                                                      \
      page_touch_ ## page_name(this, state, point);                            \
      break;
    PAGE_TYPES(V)
#undef V
  }
}

void Controller::touchend(AppState& state) {
    switch (state.get_page()) {
#define V(page_name)                                                           \
    case Page::page_name:                                                      \
      page_touchend_ ## page_name(this, state);                                \
      break;
    PAGE_TYPES(V)
#undef V
  }
}

}  // namespace screen
}  // namespace synth
