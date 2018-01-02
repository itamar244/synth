#include "screen/screen.h"
#include <TFT9341.h>
#include "app-state.h"
#include "screen/pages.h"

#define PAGE_TYPES(V) V(INDEX) V(KEYBOARD)

namespace synth {
namespace screen {

Point get_clicked_point() {
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
#define PAINT_SCREEN(page_name)                                                \
      case Page::page_name:                                                    \
        buttons_ = screen_ ## page_name();                                     \
        break;
      PAGE_TYPES(PAINT_SCREEN)
#undef PAINT_SCREEN
    }
  }
}

void Controller::tap(AppState& state) {
  Point point = get_clicked_point();

  switch (state.get_page()) {
#define TAP_SCREEN(page_name)                                                  \
    case Page::page_name:                                                      \
      tap_ ## page_name(this, state, point);                                   \
      break;
    PAGE_TYPES(TAP_SCREEN)
#undef TAP_SCREEN
  }
}

}  // namespace screen
}  // namespace synth
