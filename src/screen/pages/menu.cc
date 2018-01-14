#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"

#define MENU_ITEMS 3
#define SYNTH_MENU_ITEM_TYPES(V)                                               \
  V(Keyboard)                                                                  \
  V(PracticePlayerList)                                                        \
  V(Settings)

namespace synth {
namespace screen {

const char* kMenuButtonNames[MENU_ITEMS] = {
  "Keyboard",
  "Practice Player",
  "Settings",
};

#define V(TYPE) k ## TYPE,
enum Setting {
  SYNTH_MENU_ITEM_TYPES(V)
};
#undef V

PAGE_PAINT(Menu) {
  return PaintMenu(kMenuButtonNames, MENU_ITEMS);
}

PAGE_TOUCH(Menu) {
  IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			switch (index) {
#define V(PAGE)                                                              \
				case k ## PAGE:                                                      \
					controller->set_page(Page::k ## PAGE);                             \
					break;
				SYNTH_MENU_ITEM_TYPES(V)
#undef V
			}
  	});
}

PAGE_TOUCHEND(Menu) {
	ClearButtonClicks(buttons);
}

} // namespace screen
} // namespace synth
