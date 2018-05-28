#include "screen/routes.h"
#include <TFT9341.h>
#include "utils.h"
#include "serial_communication.h"

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
			auto& state = env.state();
			auto comparator = state.player->ToComparator();

			switch (index) {
				case 0: // Back
					controller->set_route(Route::kPracticePlayerList);
					if (comparator != nullptr) {
						env.audio()->RemoveTones(comparator->phrase_tones());
						// should delete player, because it will
						// set `state.player` to nullptr instead of just deleting it.
						utils::DeletePtr(state.player);
					}
					break;
				case 1: // Start
					state.is_song_played = true;
					break;
				case 2: // Commit
					if (comparator->NextSection()) {
						state.is_song_played = true;
					} else {
						PaintGrade(comparator->grade());
					}
					break;
			}
		});
}

ROUTE_TOUCHEND(PracticePlayerPlaying) { Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
