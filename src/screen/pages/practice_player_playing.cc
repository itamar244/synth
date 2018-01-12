#include "screen/pages.h"

#define MENU_ITEMS 3

namespace synth {
namespace screen {

const char* kPracticePlayingButtons[MENU_ITEMS] = {
	"Back",
	"Start",
	"Commit",
};

PAGE_PAINT(PracticePlayerPlaying) {
  return PaintMenu(kPracticePlayingButtons, MENU_ITEMS);
}

PAGE_TOUCH(PracticePlayerPlaying) {
  IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			switch (index) {
				case 0:
					controller->set_page(Page::kPracticePlayerList);
					break;
				case 1:
					env.PlaySong();
					break;
				case 2:
					env.PauseSong();
					break;
			}
		});
}

PAGE_TOUCHEND(PracticePlayerPlaying) { ClearButtonClicks(buttons); }

} // namespace screen
} // namespace synth
