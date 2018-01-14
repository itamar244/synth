#include "screen/pages.h"
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

MelodyComparator* comparator = nullptr;

void PaintGrade(float grade) {
	uint16_t x = lcd.getWidth() / 2 + 50;
	uint16_t y = lcd.getHeight() / 2 - 40;
	lcd.drawRect(x, y, 100, 40, Color::WHITE);
	lcd.gotoxy(x + 20, y + 15);
	lcd.setBackground(Color::BLACK);
	lcd.print(grade);
}

PAGE_PAINT(PracticePlayerPlaying) {
  return PaintMenu(kPracticePlayingButtons, MENU_ITEMS);
}

PAGE_TOUCH(PracticePlayerPlaying) {
  IterateThroughPressedButtons(buttons, point,
		[&](uint8_t index) {
			switch (index) {
				case 0:
					controller->set_page(Page::kPracticePlayerList);
					if (comparator != nullptr) {
						env.audio()->RemoveTones(comparator->phrase_tones());
						utils::DeletePtr(comparator);
					}
					break;
				case 1:
					if (comparator == nullptr) {
						comparator = new MelodyComparator(*env.song_container());
						env.SetMelodyComparator(comparator);
					}
					env.PlaySong();
					break;
				case 2:
					if (comparator != nullptr && !comparator->NextSection()) {
						PaintGrade(comparator->grade());
					}
					break;
			}
		});
}

PAGE_TOUCHEND(PracticePlayerPlaying) { ClearButtonClicks(buttons); }

} // namespace screen
} // namespace synth
