#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"


namespace synth {
namespace screen {

std::vector<Button> PaintMenu(const char* button_names[], uint8_t size) {
  std::vector<Button> buttons;
  buttons.reserve(size);

  for (uint8_t i = 0; i < size; i++) {
    const uint16_t x = 30;
    const uint16_t y = i * 50 + 20;
    const int width = 150, height = 40;

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.print(button_names[i]);
  }

  return buttons;
}

} // namespace synth
} // namespace screen
