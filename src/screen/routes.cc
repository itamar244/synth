/**
 * exported functions for repeated patterns
 * that are used in `screen/pages/` files to
 * generate screen output.
 */
#include <StandardCplusplus.h>
#include <cstring>
#include <initializer_list>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/routes.h"

namespace synth {
namespace screen {

void ClearButtonClicks(std::vector<Button>& buttons) {
	for (auto& button : buttons) {
		if (button.is_pressed) {
			button.is_pressed = false;
		}
	}
}

std::vector<Button> PaintMenu(
		const std::initializer_list<const char*>& names) {
  std::vector<Button> buttons;
	uint8_t i = 0;
  buttons.reserve(names.size());

  for (auto name : names) {
		uint8_t name_len = std::strlen(name);
    uint16_t x = 30, y = i++ * 50 + 20;
    uint8_t width = 80, height = 40;

		if (name_len > 4) {
			width = name_len * 12 + 36;
		}
    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.print(name);
  }

  return buttons;
}

} // namespace synth
} // namespace screen
