#include "screen.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

using utils::Button;
using std::vector;

namespace {

vector<Button> screen0() {
  uint8_t size = 7;
  char keys[size] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
  vector<Button> buttons;
  buttons.reserve(size);

  for (uint8_t i = 0; i < size; i++) {
    const int x = (i % 3) * 100;
    const int y = (i / 3) * 100;
    const int width = 50, height = 20;

    buttons.push_back({ x, y, width, height, String(keys[i]) });
    lcd.fillRoundRect(x, y, width, height, 5, YELLOW);
    lcd.gotoxy(x + 5, y + 5);
    lcd.write(keys[i]);
  }
  return buttons;
}

}  // namespace

void Screen::switch_screen() {
  painted = false;
}

void Screen::paint() {
  if (!painted) {
    painted = true;
    lcd.setBackground(BLACK);
    lcd.clrscr();
    lcd.setColor(RED);

    switch (screen_index) {
      case 0: buttons = screen0(); break;
    }
  }
}

void Screen::tap(uint16_t x, uint16_t y) {
  for (const auto& button : buttons) {
    const int diff_x = x - button.x, diff_y = y - button.y;

    if (
      diff_x < button.width && diff_x > 0
      && diff_y < button.height && diff_y > 0
    ) {
      Serial.println(button.text);
      return;
    }
  }
}

}  // namespace synth
