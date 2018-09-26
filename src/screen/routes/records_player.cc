#include "screen/routes.h"
#include "recorder.h"

namespace synth {
namespace screen {

namespace {

// used to store the keyboard value
uint8_t keyboard_value = 0;

} // namespace

ROUTE_INIT(RecordsPlayer) {
	keyboard_value = 0;
	return PaintKeyboard(window, {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Run",
	});
}

ROUTE_TOUCH(RecordsPlayer) {
	auto size = state.buttons.size();

	state.IteratePressedButtons([&](uint8_t index) {
		if (index == size - 1) {
			state.controller->set_route(Route::kMenu);
		} else if (index == size - 2) {
			state.env.SetPlayer(new RecordsPlayer(keyboard_value));
			keyboard_value = 0;
		} else {
			keyboard_value = keyboard_value * 10 + index;
		}
	});
}

} // namespace screen
} // namespace synth
