#include "screen/pages.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/page.h"
#include "screen/screen.h"

#define NOTE_ITEMS 7
const char NOTE_VALUES[NOTE_ITEMS] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

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

PAGE_TAP(INDEX) {
  if (controller->get_buttons()[0].is_tapped(point)) {
    // Serial.println(String(x) + ", " + String(y));
    state.switch_page(Page::KEYBOARD);
  }
}

PAGE_SCREEN(KEYBOARD) {
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

PAGE_TAP(KEYBOARD) {
  auto& buttons = controller->get_buttons();
  
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.is_tapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        state.start_note(NOTE_VALUES[i]);
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }

    if (button.is_pressed) {
      // solves some quirks that the screen is pressed in another place.
      // waits a milisecond and rechecks if the button is held
      delay(1);
      if (digitalRead(2) != 0 && !button.is_tapped(get_clicked_point())) {
        button.is_pressed = false;
        state.stop_note(NOTE_VALUES[i]);
      }
    }
  }
}

} // namespace screen
} // namespace synth
