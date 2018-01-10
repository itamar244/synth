#include <Arduino.h>
#include <TFT9341.h>
#include "screen/button.h"
#include "screen/pages.h"
#include "song_player/songs.h"

#define SONG_ITEMS 3

namespace synth {
namespace screen {

const char* kSongButtonNames[SONG_ITEMS] = {
  "Back",
  "The Small Jonathan",
	"Seven Nation Army",
};

PAGE_PAINT(PracticePlayer) {
  return PaintMenu(kSongButtonNames, SONG_ITEMS);
}

PAGE_TOUCH(PracticePlayer) {
  for (unsigned i = 0; i < buttons.size(); i++) {
    Button& button = buttons[i];

    if (button.IsTapped(point)) {
      if (!button.is_pressed) {
        button.is_pressed = true;
				switch (i) {
					case 0:
						controller->set_page(Page::kMenu);
						break;
#define SYNTH_PLAY_SONG_CASE(INDEX, SONG)                                      \
					case INDEX:                                                          \
						env.PlaySong(                                                      \
							songs::SONG,                                                     \
							sizeof(songs::SONG) / sizeof(songs::SONG[0]));                   \
						break;
					SYNTH_PLAY_SONG_CASE(1, THE_SMALL_JONATHAN)
					SYNTH_PLAY_SONG_CASE(2, SEVEN_NATION_ARMY)
#undef SYNTH_PLAY_SONG_CASE
				}
      }
      // doesn't need to continue checking because multitouching isn't supported
      return;
    }
  }
}

PAGE_TOUCHEND(PracticePlayer) { ClearButtonClicks(buttons); }

} // namespace screen
} // namespace synth
