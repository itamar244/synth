#include "screen/pages.h"
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/screen.h"
#include "screen/button.h"

const char NOTE_VALUES[] PROGMEM = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

namespace synth {
namespace screen {

PAGE_SCREEN(INDEX) {
  const int width = 120, height = 40;
  const uint16_t x = lcd.getWidth() / 2 - width / 2;
  const uint16_t y = lcd.getHeight() / 2 - height / 2;
  Button button = { x, y, width, height };
  
  lcd.gotoxy(x - 60, y - 20);
  lcd.print("Itamar Yatom Project");
  lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
  lcd.gotoxy(x + 5, y + 5);
  lcd.print("continue");

  return {button};
}

PAGE_TAP(INDEX) {
  if (controller->get_buttons().at(0).is_clicked(x, y)) {
    // Serial.println(String(x) + ", " + String(y));
    controller->switch_page(Page::KEYBOARD);
  }
}

PAGE_SCREEN(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  std::vector<Button> buttons;
  buttons.reserve(size);

  for (uint8_t i = 0; i < size; i++) {
    const int x = (i % 3) * 100;
    const int y = (i / 3) * 100;
    const int width = 50, height = 40;
    const char key = pgm_read_byte_near(NOTE_VALUES + i);

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::YELLOW);
    lcd.gotoxy(x + 5, y + 5);
    lcd.write(key);
  }
  return buttons;
}

PAGE_TAP(KEYBOARD) {
  auto buttons = controller->get_buttons();
  // Serial.println("Tapped: " + String(x) + ", " + String(y));
  for (unsigned i = 0; i < buttons.size(); i++) {
    const Button& button = buttons[i];
    
    if (button.is_clicked(x, y)) {
      Serial.println((char)pgm_read_byte_near(NOTE_VALUES + i));
      return;
    }
  }
}

} // namespace screen
} // namespace synth
