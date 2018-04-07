#include "screen/routes.h"
#include <Arduino.h>
#include <TFT9341.h>
#include "screen/button.h"
#include "melody_player/melodies.h"

#define SONG_ITEMS 3

namespace synth {
namespace screen {

ROUTE_INIT(PracticePlayerList) {
	return PaintMenu({
		"Back",
		"The Small Jonathan",
		"Seven Nation Army",
	});
}

ROUTE_TOUCH(PracticePlayerList) {
	IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			controller->set_route(Route::kPracticePlayerPlaying);

			switch (index) {
				case 0:
					controller->set_route(Route::kMenu);
					break;
#define SYNTH_PLAY_SONG_CASE(INDEX, SONG)                                      \
				case INDEX:                                                            \
					env.InitMelodyComparator(                                            \
						melodies::SONG,                                                    \
						sizeof(melodies::SONG) / sizeof(melodies::SONG[0]),                \
						melodies::SONG ## _PRACTICE_SECTIONS);                             \
					break;
				SYNTH_PLAY_SONG_CASE(1, THE_SMALL_JONATHAN)
				SYNTH_PLAY_SONG_CASE(2, SEVEN_NATION_ARMY)
#undef SYNTH_PLAY_SONG_CASE
			}
		});
}

ROUTE_TOUCHEND(PracticePlayerList) { ClearButtonClicks(buttons); }

} // namespace screen
} // namespace synth
