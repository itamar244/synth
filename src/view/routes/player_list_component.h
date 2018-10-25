#pragma once

#include <cstdint>
#include <initializer_list>
#include <functional>
#include <string>
#include <atic/iterables.h>
#include "view/routes.h"
#include "view/button.h"

namespace synth::view {

static const std::initializer_list<const std::string> kMelodyNames = {
	"seven-nation-army",
};

inline std::vector<Button> PlayerListInit(sf::RenderWindow& window) {
	return PaintMenu(window, {
		{ "Back" },
		kMelodyNames,
	});
}

inline auto PlayerListTouchHandler(
		RouteState& state,
		const std::function<void(const std::string&)>& set_player) {
	state.IteratePressedButtons([&](uint8_t index) {
		auto& env = state.env;

		if (index == 0) {
			state.controller->set_route(Route::kMenu);
			env.DeletePlayer();
		} else {
			auto file_name = atic::Advance(kMelodyNames.begin(), index - 1);
			set_player("melodies-data/" + file_name + ".melo");
		}
	});
}

} // namespace synth::view
