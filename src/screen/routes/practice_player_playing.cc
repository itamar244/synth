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
			switch (index) {
				case 0: // Back
					controller->set_route(Route::kPracticePlayerList);
					env.DeletePlayer();
					break;
				case 1: // Start
					env.StartPlaying();
					break;
				case 2: // Commit
					auto status = env.ComparatorNextSection();
					if (!status.first) {
						PaintGrade(status.second);
					}
					break;
			}
		});
}

} // namespace screen
} // namespace synth
