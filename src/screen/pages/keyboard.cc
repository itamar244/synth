#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"

#define TONE_ITEMS 7
const char TONE_NAMES[TONE_ITEMS] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
const uint8_t TONE_VALUES[TONE_ITEMS] = { 0, 2, 4, 5, 7, 9, 11 };

namespace synth {
namespace screen {

PAGE_PAINT(KEYBOARD) {
  std::vector<Button> buttons;
  buttons.reserve(TONE_ITEMS + 1);

  for (uint8_t i = 0; i < TONE_ITEMS; i++) {
    const uint16_t x = (i % 3) * 100 + 30;
    const uint16_t y = (i / 3) * 50 + 40;
    const int width = 50, height = 40;
    const char key = TONE_NAMES[i];

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.write(key);
  }

  Button toggle_button = { lcd.getWidth() - 120, lcd.getHeight() - 50, 110, 40 };
  buttons.push_back(toggle_button);
  lcd.fillRoundRect(
    toggle_button.x, toggle_button.y, 
    toggle_button.width, toggle_button.height, 5, Color::RED);
  lcd.gotoxy(toggle_button.x + 18, toggle_button.y + 10);
  lcd.setColor(Color::WHITE, Color::RED);
  lcd.print("TOGGLE");

  return buttons;
}

PAGE_TOUCH(KEYBOARD) {
  const auto& size = buttons.size();
  for (unsigned i = 0; i < size; i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        if (i != size - 1) {
          env.audio()->AddTone(TONE_VALUES[i] + env.GetOctaveDif());
        } else {
          env.ToggleOctaveLevel();
        }
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
}

PAGE_TOUCHEND(KEYBOARD) {
  const auto& size = buttons.size();
  for (unsigned i = 0; i < size; i++) {
    Button& button = buttons[i];
    
    if (button.is_pressed) {
      button.is_pressed = false;
      if (i != size - 1) {
        env.audio()->RemoveTone(TONE_VALUES[i] + env.GetOctaveDif());
      }
    }
  }
}

} // namespace screen
} // namespace synth
