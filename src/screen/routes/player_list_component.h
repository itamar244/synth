#pragma once

#include <cstdint>
#include <initializer_list>
#include <string>
#include <SFML/Graphics.hpp>
#include <atic/iterables.h>
#include "screen/routes.h"
#include "screen/button.h"

namespace synth {

const std::initializer_list<const std::string> kMelodyNames = {
	"seven-nation-army",
};

namespace screen {

inline std::vector<Button> PlayerListInit(sf::RenderWindow& window) {
	return PaintMenu(window, {
		{ "Back" },
		kMelodyNames,
	});
}

template<typename PlayerType, typename Callback>
inline auto PlayerListTouchHandler(
		Controller* controller,
		Environment& env,
		const Callback& on_melody_set) {
	return [&](uint8_t index) {
			if (index == 0) {
				controller->set_route(Route::kMenu);
				env.DeletePlayer();
			} else {
				on_melody_set();
				const std::string file_name =
						atic::Advance(kMelodyNames.begin(), index - 1);
				env.SetPlayer<PlayerType>("melodies-data/" + file_name + ".melo");
			}
		};
}

} // namespace screen
} // namespace synth
