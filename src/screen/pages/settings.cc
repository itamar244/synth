#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"

#define BUTTON_ITEMS 2
#define SYNTH_SETTING_TYPES(V)                                                 \
  V(Back)                                                                      \
  V(Audio)

namespace synth {
namespace screen {

#define V(TYPE) #TYPE,
const char* BUTTON_NAMES[BUTTON_ITEMS] = {
  SYNTH_SETTING_TYPES(V)
};
#undef V

#define V(TYPE) k ## TYPE,
enum Setting {
  SYNTH_SETTING_TYPES(V)
};
#undef V

PAGE_PAINT(Settings) {
  std::vector<Button> buttons;
  buttons.reserve(BUTTON_ITEMS + 1);

  for (uint8_t i = 0; i < BUTTON_ITEMS; i++) {
    const uint16_t x = 30;
    const uint16_t y = i * 50 + 40;
    const int width = 150, height = 40;

    buttons.push_back({ x, y, width, height });
    lcd.fillRoundRect(x, y, width, height, 5, Color::RED);
    lcd.gotoxy(x + 18, y + 10);
    lcd.setColor(Color::WHITE, Color::RED);
    lcd.print(BUTTON_NAMES[i]);
  }

  return buttons;
}

PAGE_TOUCH(Settings) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        switch (i) {
          case kBack:
            controller->set_page(Page::kKeyboard);
            break;
          case kAudio:
            env.SetAudioType(
              env.audio()->IsType(Audio::kBuiltin)
                ? Audio::kSerialPort : Audio::kBuiltin);
            break;
        }
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
}

PAGE_TOUCHEND(Settings) {
  for (auto& button : buttons) {
    if (button.is_pressed) {
      button.is_pressed = false;
    }
  }
}

} // namespace screen
} // namespace synth
