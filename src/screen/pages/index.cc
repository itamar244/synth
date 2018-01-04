#include "screen/pages.h"
#include <Arduino.h>
#include <TFT9341.h>
#include "screen/page.h"

namespace synth {
namespace screen {

PAGE_SCREEN(INDEX) {
  const int width = 120, height = 40;
  const uint16_t x = lcd.getWidth() / 2 - width / 2;
  const uint16_t y = lcd.getHeight() / 2 - height / 2;

  lcd.gotoxy(x - 60, y - 20);
  lcd.setColor(Color::WHITE, Color::BLACK);
  lcd.print("Itamar Yatom Project");
  lcd.fillRoundRect(x, y, width, height, 5, Color::BLUE);
  lcd.gotoxy(x + 12, y + 10);
  lcd.setColor(Color::WHITE, Color::BLUE);
  lcd.print("continue");

  return {{ x, y, width, height }};
}

PAGE_TOUCH(INDEX) {
  if (controller->get_buttons()[0].is_tapped(point)) {
    // Serial.println(String(x) + ", " + String(y));
    state.switch_page(Page::KEYBOARD);
  }
}

PAGE_TOUCHEND(INDEX) {}

} // namespace screen
} // namespace synth
