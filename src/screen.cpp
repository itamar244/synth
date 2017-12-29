#include "screen.h"
#include <TFT9341.h>

#define PAGE_TYPES(V) V(INDEX) V(KEYBOARD)
#define SCREEN(page) vector<Button> screen_ ## page()
#define TAP(page) \
  void tap_ ## page(uint16_t x, uint16_t y, Screen* screen)

const char NOTE_VALUES[] PROGMEM = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

namespace synth {

using utils::Button;
using std::vector;

namespace {

SCREEN(INDEX) {
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

TAP(INDEX) {
  if (screen->get_buttons().at(0).is_clicked(x, y)) {
    Serial.println(String(x) + ", " + String(y));
    screen->switch_page(Page::KEYBOARD);
  }
}

SCREEN(KEYBOARD) {
  uint8_t size = strlen_P(NOTE_VALUES);
  vector<Button> buttons;
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

TAP(KEYBOARD) {
  auto buttons = screen->get_buttons();
  // Serial.println("Tapped: " + String(x) + ", " + String(y));
  for (unsigned i = 0; i < buttons.size(); i++) {
    const Button& button = buttons[i];
    
    if (button.is_clicked(x, y)) {
      Serial.println((char)pgm_read_byte_near(NOTE_VALUES + i));
      return;
    }
  }
}

}  // namespace

void Screen::switch_page(Page to) {
  painted = false;
  // limiting the screen to maximum types of screens
  current_page = to;
}

void Screen::paint() {
  if (!painted) {
    painted = true;
    lcd.setBackground(Color::BLACK);
    lcd.clrscr();
    lcd.setColor(Color::RED);

    switch (current_page) {
#define PAINT_SCREEN(page_name)                                                \
      case Page::page_name: buttons = screen_ ## page_name(); break;
      PAGE_TYPES(PAINT_SCREEN)
#undef PAINT_SCREEN
    }
  }
}

void Screen::tap(uint16_t x, uint16_t y) {
  switch (current_page) {
#define TAP_SCREEN(page_name)                                                \
    case Page::page_name: tap_ ## page_name(x, y, this); break;
    PAGE_TYPES(TAP_SCREEN)
#undef TAP_SCREEN
  }
}

}  // namespace synth
