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

PAGE_PAINT(Keyboard) {
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

  Button settings = { lcd.getWidth() - 140, lcd.getHeight() - 50, 140, 40 };
  buttons.push_back(settings);
  lcd.fillRoundRect(
    settings.x, settings.y,
    settings.width, settings.height, 5, Color::RED);
  lcd.gotoxy(settings.x + 18, settings.y + 10);
  lcd.setColor(Color::WHITE, Color::RED);
  lcd.print("SETTINGS");

  return buttons;
}

PAGE_TOUCH(Keyboard) {
  const auto& size = buttons.size() - 1;
  for (unsigned i = 0; i < size; i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        env.audio()->AddTone(env.AddOctaveDiff(TONE_VALUES[i]));
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
  Button& toggle = buttons.back();
  if (toggle.IsTapped(point)) {
    env.set_page(Page::kSettings);
  }
}

PAGE_TOUCHEND(Keyboard) {
  const auto& size = buttons.size();
  for (unsigned i = 0; i < size; i++) {
    Button& button = buttons[i];
    
    if (button.is_pressed) {
      button.is_pressed = false;
      if (i != size - 1) {
        env.audio()->RemoveTone(env.AddOctaveDiff(TONE_VALUES[i]));
      }
    }
  }
}

} // namespace screen
} // namespace synth
