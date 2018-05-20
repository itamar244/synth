/**
 * exported functions for repeated patterns
 * that are used in `screen/pages/` files to
 * generate screen output.
 */
#include "screen/routes.h"
#include <StandardCplusplus.h>
#include <cstring>
#include <algorithm>
#include <initializer_list>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include <StandardCplusplus.h>

namespace synth {
namespace screen {

void ClearButtonClicks(std::vector<Button>& buttons) {
	for (auto& button : buttons) {
		if (button.is_pressed) {
			button.is_pressed = false;
		}
	}
}

_PaintMenuStats PaintMenuWithStats(
		const std::initializer_list<const char*>& names) {
  std::vector<Button> buttons;
	uint8_t i = 0;
	uint16_t max_width = 0;
  buttons.reserve(names.size());

  for (auto name : names) {
		uint8_t name_len = std::strlen(name);
    uint16_t x = 30, y = (i++) * 50 + 20;
    uint16_t width = 80, height = 40;

		if (name_len > 4) {
			width = name_len * 12 + 36;
		}
		max_width = std::max(width, max_width);
    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.print(name);
  }

  return {max_width, buttons};
}

std::vector<Button> PaintMenu(
		const std::initializer_list<const char*>& names) {
	return PaintMenuWithStats(names).buttons;
}

std::vector<Button> PaintKeyboard(const char names[], uint16_t size) {
	std::vector<Button> buttons;
  buttons.reserve(size + 1);

  for (uint8_t i = 0; i < size; i++) {
    const uint16_t x = (i % 3) * 100 + 30;
    const uint16_t y = (i / 3) * 50 + 40;
    const int width = 50, height = 40;

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.write(names[i]);
  }

  Button menu = { lcd.getWidth() - 100, lcd.getHeight() - 50, 100, 40 };
  buttons.push_back(menu);
  lcd.fillRoundRect(
    menu.x, menu.y,
    menu.width, menu.height, 5, Color::RED);
  lcd.gotoxy(menu.x + 18, menu.y + 10);
  lcd.setColor(Color::WHITE, Color::RED);
  lcd.print("Back");

  return buttons;
}

} // namespace synth
} // namespace screen
