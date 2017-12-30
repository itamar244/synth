#include "screen/pages.h"
#include <TFT9341.h>
#include "app-state.h"
#include "screen/button.h"
#include "screen/page.h"
#include "screen/screen.h"

const char NOTE_VALUES[] PROGMEM = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

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

  controller->set_buttons(
    new Button[1]{{ x, y, width, height }},
    1
  );
}

PAGE_TAP(INDEX) {
  if (controller->get_buttons()[0].is_tapped(x, y)) {
    // Serial.println(String(x) + ", " + String(y));
    state.switch_page(Page::KEYBOARD);
  }
}

PAGE_SCREEN(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  Button* buttons = new Button[size];

  for (uint8_t i = 0; i < size; i++) {
    const uint16_t x = (i % 3) * 100 + 30;
    const uint16_t y = (i / 3) * 50 + 40;
    const int width = 50, height = 40;
    const char key = pgm_read_byte_near(NOTE_VALUES + i);

    buttons[i] = { x, y, width, height };
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.write(key);
  }


  controller->set_buttons(buttons, size);
}

PAGE_TAP(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  auto buttons = controller->get_buttons();
  // Serial.println("Tapped: " + String(x) + ", " + String(y));
  for (unsigned i = 0; i < size; i++) {
    Button& button = buttons[i];

    if (button.is_tapped(x, y)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        // TODO: should connect this to Audio module to make sounds
        Serial.println("p" + String((char)pgm_read_byte_near(NOTE_VALUES + i)));
      }
      return;
    } else if (button.is_pressed) {
      button.is_pressed = false;
      Serial.println("u" + String((char)pgm_read_byte_near(NOTE_VALUES + i)));
    }
  }
}

} // namespace screen
} // namespace synth
