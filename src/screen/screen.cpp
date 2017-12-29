#include "screen/screen.h"
#include <TFT9341.h>

#define PAGE_TYPES(V) V(INDEX) V(KEYBOARD)

namespace synth {
namespace screen {

void Controller::switch_page(Page to) {
  painted = false;
  current_page = to;
}

void Controller::paint() {
  if (!painted) {
    painted = true;
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    switch (current_page) {
#define PAINT_SCREEN(page_name)                                                \
      case Page::page_name:                                                    \
        buttons = screen_ ## page_name();                                      \
        break;
      PAGE_TYPES(PAINT_SCREEN)
#undef PAINT_SCREEN
    }
  }
}

void Controller::tap(uint16_t x, uint16_t y) {
  switch (current_page) {
#define TAP_SCREEN(page_name)                                                \
    case Page::page_name:                                                    \
      tap_ ## page_name(x, y, this);                                         \
      break;
    PAGE_TYPES(TAP_SCREEN)
#undef TAP_SCREEN
  }
}

}  // namespace screen
}  // namespace synth
