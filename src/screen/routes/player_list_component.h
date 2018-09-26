#pragma once

#include <cstdint>
#include <initializer_list>
#include <functional>
#include <string>
#include <atic/iterables.h>
#include "screen/routes.h"
#include "screen/button.h"

namespace synth::screen {

static const std::initializer_list<const std::string> kMelodyNames = {
	"seven-nation-army",
};

inline std::vector<Button> PlayerListInit(sf::RenderWindow& window) {
	return PaintMenu(window, {
		{ "Back" },
		kMelodyNames,
	});
}

template<typename PlayerType>
inline auto PlayerListTouchHandler(
		RouteState& state,
		const std::function<void(void)>& on_melody_set) {
	state.IteratePressedButtons([&](uint8_t index) {
		auto& env = state.env;

		if (index == 0) {
			state.controller->set_route(Route::kMenu);
			env.DeletePlayer();
		} else {
			const std::string file_name =
					atic::Advance(kMelodyNames.begin(), index - 1);
			env.SetPlayer<PlayerType>("melodies-data/" + file_name + ".melo");
			on_melody_set();
		}
	});
}

} // namespace synth::screen
