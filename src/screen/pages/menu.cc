#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"

#define MENU_ITEMS 2
#define SYNTH_MENU_ITEM_TYPES(V)                                               \
  V(Keyboard)                                                                  \
  V(Settings)

namespace synth {
namespace screen {

#define V(TYPE) #TYPE,
const char* kMenuButtonNames[MENU_ITEMS] = {
  SYNTH_MENU_ITEM_TYPES(V)
};
#undef V

#define V(TYPE) k ## TYPE,
enum Setting {
  SYNTH_MENU_ITEM_TYPES(V)
};
#undef V

PAGE_PAINT(Menu) {
  return PaintMenu(kMenuButtonNames, MENU_ITEMS);
}

PAGE_TOUCH(Menu) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
        switch (i) {
#define SYNTH_SWITCH_PAGE(PAGE)                                                \
          case k ## PAGE:                                                      \
            controller->set_page(Page::k ## PAGE);                             \
            break;
					SYNTH_MENU_ITEM_TYPES(SYNTH_SWITCH_PAGE)
#undef SYNTH_MENU_ITEM_TYPES
        }
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
}

PAGE_TOUCHEND(Menu) {
  for (auto& button : buttons) {
    if (button.is_pressed) {
      button.is_pressed = false;
    }
  }
}

} // namespace screen
} // namespace synth
