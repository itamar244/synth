#include "screen/routes.h"
#include "serial_communication.h"
#include "recorder.h"

#define BUTTON_ITEMS 11

namespace synth {
namespace screen {

namespace {

// used to store the keyboard value
uint8_t keyboard_value = 0;

const char* kRecordsPlayerButtonNames[BUTTON_ITEMS] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Run",
};

} // namespace

ROUTE_INIT(RecordsPlayer) {
	keyboard_value = 0;
	return PaintKeyboard(kRecordsPlayerButtonNames, BUTTON_ITEMS);
}

ROUTE_TOUCH(RecordsPlayer) {
	auto size = buttons.size();

	Button::IteratePressed(buttons, point,
		[&] (uint8_t index) {
			auto& player = env.state().player;

			if (index == size - 1) {
    		controller->set_route(Route::kMenu);
				if (player != nullptr) {
					utils::DeletePtr(player);
				}
			} else if (index == size - 2) {
				utils::SetPtr<Player*>(player, new RecordsPlayer(keyboard_value));
				keyboard_value = 0;
			} else {
				keyboard_value = keyboard_value * 10 + index;
			}
		});
}

} // namespace screen
} // namespace synth
