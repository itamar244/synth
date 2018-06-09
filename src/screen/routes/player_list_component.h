#pragma once

#include "screen/routes.h"
#include <Arduino.h>
#include "screen/button.h"
#include "utils.h"

namespace synth {

using melodies::kMelodyNames;

namespace screen {

inline std::vector<Button> PlayerListInit() {
	return PaintMenu({
		{ "Back" },
		kMelodyNames,
	});
}

template<typename PlayerType, typename Callback>
inline auto PlayerListTouchHandler(
		Controller* controller, Environment& env, const Callback& on_melody_set) {
	return [&](uint8_t index) {
			if (index == 0) {
				controller->set_route(Route::kMenu);
				env.DeletePlayer();
			} else {
				on_melody_set();
				env.SetPlayer<PlayerType>(
						utils::Advance(kMelodyNames.begin(), index - 1));
			}
		};
}

} // namespace screen
} // namespace synth
