#include "screen/routes.h"
#include <Arduino.h>
#include <TFT9341.h>
#include "screen/button.h"
#include "song_player/songs.h"

#define SONG_ITEMS 3

namespace synth {
namespace screen {

const char* kSongButtonNames[SONG_ITEMS] = {
  "Back",
  "The Small Jonathan",
	"Seven Nation Army",
};

ROUTE_INIT(PracticePlayerList) {
	return PaintMenu(kSongButtonNames, SONG_ITEMS);
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
						songs::SONG,                                                       \
						sizeof(songs::SONG) / sizeof(songs::SONG[0]),                      \
						songs::SONG ## _PRACTICE_SECTIONS);                                \
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
