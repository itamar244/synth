#include "screen/routes.h"
#include <Arduino.h>
#include "melody_player/melodies.h"
#include "melody_player/melody_comparator.h"
#include "screen/button.h"
#include "utils.h"

namespace synth {

using melodies::kMelodyNames;

namespace screen {

ROUTE_INIT(PracticePlayerList) {
	return PaintMenu({
		{ "Back" },
		kMelodyNames,
	});
}

ROUTE_TOUCH(PracticePlayerList) {
	Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			if (index == 0) {
				controller->set_route(Route::kMenu);
			} else {
				controller->set_route(Route::kPracticePlayerPlaying);
				env.SetPlayer<MelodyComparator>(
					utils::Advance(kMelodyNames.begin(), index - 1));
			}
		});
}

} // namespace screen
} // namespace synth
