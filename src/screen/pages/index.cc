#include <Arduino.h>
#include <TFT9341.h>
#include "screen/pages.h"

namespace synth {
namespace screen {

PAGE_PAINT(Index) {
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

PAGE_TOUCH(Index) {
  if (buttons[0].IsTapped(point)) {
    // Serial.println(String(x) + ", " + String(y));
    env.set_page(Page::kKeyboard);
  }
}

PAGE_TOUCHEND(Index) {}

} // namespace screen
} // namespace synth
