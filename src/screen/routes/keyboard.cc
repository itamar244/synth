#include "screen/routes.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"

#define BUTTON_ITEMS 9

namespace synth {
namespace screen {

const char* kKeyboardButtonNames[BUTTON_ITEMS] = {
	"C", "D", "E", "F", "G", "A", "B", "-", "+",
};
const uint8_t kToneValues[] = { 0, 2, 4, 5, 7, 9, 11 };

ROUTE_INIT(Keyboard) {
  return PaintKeyboard(kKeyboardButtonNames, BUTTON_ITEMS);
}

ROUTE_TOUCH(Keyboard) {
	const uint8_t size = buttons.size();
  Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			if (index < size - 2) {
				env.AddToneWithOctave(kToneValues[index]);
			} else if (index == size - 1) {
    		controller->set_route(Route::kMenu);
			} else if (kKeyboardButtonNames[index][0] == '-') {
				env.DecrementOctave();
			} else {
				env.IncrementOctave();
			}
  	});
}

ROUTE_TOUCHEND(Keyboard) {
  Button::IterateUnpressed(buttons,
		[&env](uint8_t index) {
			if (index < BUTTON_ITEMS) {
				env.RemoveToneWithOctave(kToneValues[index]);
			}
		});
}

} // namespace screen
} // namespace synth
