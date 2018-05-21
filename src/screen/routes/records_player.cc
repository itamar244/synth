#include "screen/routes.h"
#include "recorder.h"

#define BUTTON_ITEMS 10

namespace synth {
namespace screen {

const char kRecordsPlayerButtonNames[BUTTON_ITEMS] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
};

ROUTE_INIT(RecordsPlayer) {
	return PaintKeyboard(kRecordsPlayerButtonNames, BUTTON_ITEMS);
}

ROUTE_TOUCH(RecordsPlayer) {
	IterateThroughPressedButtons(buttons, point,
		[&] (uint8_t index) {
			if (index == buttons.size() - 1) {
    		controller->set_route(Route::kMenu);
			}
		});
}

ROUTE_TOUCHEND(RecordsPlayer) {  Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
