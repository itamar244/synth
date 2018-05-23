#include "screen/routes.h"
#include "recorder.h"

namespace synth {
namespace screen {

ROUTE_INIT(Recorder) {
	return PaintMenu({
		"Back",
		"Start",
		"Stop",
	});
}

ROUTE_TOUCH(Recorder) {
	Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			auto& recorder = env.state().recorder;
			switch (index) {
				case 0: // Back
					controller->set_route(Route::kMenu);
					if (recorder != nullptr) {
						utils::DeletePtr(recorder);
					}
					break;
				case 1: // Start
					recorder = new Recorder();
					break;
				case 2: // Stop
					utils::DeletePtr(recorder);
					break;
			}
		});
}

ROUTE_TOUCHEND(Recorder) {  Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
