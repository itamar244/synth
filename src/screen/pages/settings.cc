#include <Arduino.h>
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
const char* kSettingsButtonNames[BUTTON_ITEMS] = {
  SYNTH_SETTING_TYPES(V)
};
#undef V

#define V(TYPE) k ## TYPE,
enum Setting {
  SYNTH_SETTING_TYPES(V)
};
#undef V

PAGE_PAINT(Settings) {
  return PaintMenu(kSettingsButtonNames, BUTTON_ITEMS);
}

PAGE_TOUCH(Settings) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        switch (i) {
          case kBack:
            controller->set_page(Page::kMenu);
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
  ClearButtonClicks(buttons);
}

} // namespace screen
} // namespace synth
