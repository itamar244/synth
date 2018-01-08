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
  lcd.print("Itamar Yatom Project");
  lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
  lcd.gotoxy(x + 5, y + 5);
  lcd.print("continue");

  controller->set_buttons(
    new Button[1]{{ x, y, width, height }},
    1
  );
}

PAGE_TAP(INDEX) {
  if (controller->get_buttons()[0].is_clicked(x, y)) {
    // Serial.println(String(x) + ", " + String(y));
    state.switch_page(Page::KEYBOARD);
  }
}

PAGE_SCREEN(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  Button* buttons = new Button[size];

  for (uint8_t i = 0; i < size; i++) {
    const int x = (i % 3) * 100;
    const int y = (i / 3) * 100;
    const int width = 50, height = 40;
    const char key = pgm_read_byte_near(NOTE_VALUES + i);

    buttons[i] = { x, y, width, height };
    lcd.fillRoundRect(x, y, width, height, 5, Color::YELLOW);
    lcd.gotoxy(x + 5, y + 5);
    lcd.write(key);
  }


  controller->set_buttons(buttons, size);
}

PAGE_TAP(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  auto buttons = controller->get_buttons();
  // Serial.println("Tapped: " + String(x) + ", " + String(y));
  for (unsigned i = 0; i < size; i++) {
    const Button& button = buttons[i];

    if (button.is_clicked(x, y)) {
      // TODO: should connect this to Audio module to make sounds
      Serial.println((char)pgm_read_byte_near(NOTE_VALUES + i));
      return;
    }
  }
}

} // namespace screen
} // namespace synth
