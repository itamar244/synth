#include "screen/screen.h"
#include <TFT9341.h>
#include "app-state.h"
#include "screen/pages.h"

#define PAGE_TYPES(V) V(INDEX) V(KEYBOARD)

namespace synth {
namespace screen {

void Controller::paint(AppState& state) {
  if (state.should_paint_screen()) {
    state.screen_painted();
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    switch (state.get_page()) {
#define PAINT_SCREEN(page_name)                                                \
      case Page::page_name:                                                    \
        buttons_ = screen_ ## page_name();                                      \
        break;
      PAGE_TYPES(PAINT_SCREEN)
#undef PAINT_SCREEN
    }
  }
}

void Controller::tap(AppState& state, uint16_t x, uint16_t y) {
  switch (state.get_page()) {
#define TAP_SCREEN(page_name)                                                  \
    case Page::page_name:                                                      \
      tap_ ## page_name(this, state, x, y);                                    \
      break;
    PAGE_TYPES(TAP_SCREEN)
#undef TAP_SCREEN
  }
}

}  // namespace screen
}  // namespace synth
