#include "screen/routes.h"
#include <Arduino.h>
#include "screen/button.h"
#include "melody_player/melodies.h"

namespace synth {
namespace screen {

ROUTE_INIT(Player) {
	return PaintMenu({
		"Back",
		"The Small Jonathan",
		"Seven Nation Army",
	});
}

ROUTE_TOUCH(Player) {
	Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			switch (index) {
				case 0:
					controller->set_route(Route::kMenu);
					break;
#define SYNTH_PLAY_SONG_CASE(INDEX, SONG)                                      \
				case INDEX:                                                            \
					env.InitMelodyPlayer(                                                \
						melodies::SONG,                                                    \
						sizeof(melodies::SONG) / sizeof(melodies::SONG[0]));
					break;
				SYNTH_PLAY_SONG_CASE(1, THE_SMALL_JONATHAN)
				SYNTH_PLAY_SONG_CASE(2, SEVEN_NATION_ARMY)
#undef SYNTH_PLAY_SONG_CASE
			}
		});
}

ROUTE_TOUCHEND(Player) { Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
