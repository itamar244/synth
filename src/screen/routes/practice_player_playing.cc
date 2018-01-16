#include "screen/routes.h"
#include <TFT9341.h>
#include "utils.h"
#include "song_player/melody_comparator.h"

#define MENU_ITEMS 3

namespace synth {
namespace screen {

const char* kPracticePlayingButtons[MENU_ITEMS] = {
	"Back",
	"Start",
	"Commit",
};

void PaintGrade(float grade) {
	uint16_t x = lcd.getWidth() / 2 + 50;
	uint16_t y = lcd.getHeight() / 2 - 40;
	lcd.drawRect(x, y, 100, 40, Color::WHITE);
	lcd.gotoxy(x + 20, y + 15);
	lcd.setBackground(Color::BLACK);
	lcd.print(grade);
}

ROUTE_INIT(PracticePlayerPlaying) {
	return PaintMenu(kPracticePlayingButtons, MENU_ITEMS);
}

ROUTE_TOUCH(PracticePlayerPlaying) {
	IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			auto comparator = env.comparator();
			switch (index) {
				case 0:
					controller->set_route(Route::kPracticePlayerList);
					if (comparator != nullptr) {
						env.audio()->RemoveTones(comparator->phrase_tones());
						utils::DeletePtr(comparator);
					}
					break;
				case 1:
					env.PlaySong();
					break;
				case 2:
					if (!comparator->NextSection()) {
						PaintGrade(comparator->grade());
					}
					break;
			}
		});
}

ROUTE_TOUCHEND(PracticePlayerPlaying) { ClearButtonClicks(buttons); }

} // namespace screen
} // namespace synth
