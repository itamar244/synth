#include "screen/routes.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"

#define BUTTON_ITEMS 9
#define TONE_ITEMS BUTTON_ITEMS - 2

namespace synth {
namespace screen {

const char kKeyboardButtonNames[BUTTON_ITEMS] = {
	'C', 'D', 'E', 'F', 'G', 'A', 'B', '-', '+'
};
const uint8_t kToneValues[TONE_ITEMS] = { 0, 2, 4, 5, 7, 9, 11 };

ROUTE_INIT(Keyboard) {
  std::vector<Button> buttons;
  buttons.reserve(BUTTON_ITEMS + 1);

  for (uint8_t i = 0; i < BUTTON_ITEMS; i++) {
    const uint16_t x = (i % 3) * 100 + 30;
    const uint16_t y = (i / 3) * 50 + 40;
    const int width = 50, height = 40;

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.write(kKeyboardButtonNames[i]);
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

ROUTE_TOUCH(Keyboard) {
	const uint8_t size = buttons.size();
  IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			if (index < size - 2) {
				env.AddToneWithOctave(kToneValues[index]);
			} else if (index == size - 1) {
    		controller->set_route(Route::kMenu);
			} else if (kKeyboardButtonNames[index] == '-') {
				env.DecrementOctave();
			} else {
				env.IncrementOctave();
			}
  	});
}

ROUTE_TOUCHEND(Keyboard) {
  IteratethroughUnPressedButtons(buttons,
		[&env](uint8_t index) {
			if (index < BUTTON_ITEMS) {
				env.RemoveToneWithOctave(kToneValues[index]);
			}
		});
}

} // namespace screen
} // namespace synth
