#include "screen/routes.h"
#include <TFT9341.h>
#include "utils.h"

namespace synth {
namespace screen {

inline void PaintGrade(float grade) {
	uint16_t x = lcd.getWidth() / 2 + 50;
	uint16_t y = lcd.getHeight() / 2 - 40;

	lcd.drawRect(x, y, 100, 40, Color::WHITE);
	lcd.gotoxy(x + 20, y + 15);
	lcd.setBackground(Color::BLACK);
	lcd.print(grade);
}

ROUTE_INIT(PracticePlayerPlaying) {
	return PaintMenu({
		"Back",
		"Start",
		"Commit",
	});
}

ROUTE_TOUCH(PracticePlayerPlaying) {
	Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			auto& comparator = env.comparator();
			switch (index) {
				case 0: // Back
					controller->set_route(Route::kPracticePlayerList);
					if (comparator != nullptr) {
						env.audio()->RemoveTones(comparator->phrase_tones());
						utils::DeletePtr(comparator);
					}
					break;
				case 1: // Start
					env.PlaySong();
					break;
				case 2: // Commit
					if (!comparator->NextSection()) {
						PaintGrade(comparator->grade());
					}
					break;
			}
		});
}

ROUTE_TOUCHEND(PracticePlayerPlaying) { Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
