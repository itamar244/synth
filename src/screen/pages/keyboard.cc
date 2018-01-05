#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"

#define NOTE_ITEMS 7
const char NOTE_VALUES[NOTE_ITEMS] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

namespace synth {
namespace screen {

PAGE_PAINT(KEYBOARD) {
  std::vector<Button> buttons;
  buttons.reserve(NOTE_ITEMS);

  for (uint8_t i = 0; i < NOTE_ITEMS; i++) {
    const uint16_t x = (i % 3) * 100 + 30;
    const uint16_t y = (i / 3) * 50 + 40;
    const int width = 50, height = 40;
    const char key = NOTE_VALUES[i];

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.write(key);
  }

  return buttons;
}

PAGE_TOUCH(KEYBOARD) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.is_tapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        env.audio()->add_note(NOTE_VALUES[i]);
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
}

PAGE_TOUCHEND(KEYBOARD) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];
    
    if (button.is_pressed) {
      button.is_pressed = false;
      env.audio()->remove_note(NOTE_VALUES[i]);
    }
  }
}

} // namespace screen
} // namespace synth
