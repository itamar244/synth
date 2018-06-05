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
			switch (index) {
				case 0: // Back
					controller->set_route(Route::kMenu);
					env.StopRecording();
					break;
				case 1: // Start
					env.StartRecording();
					break;
				case 2: // Stop
					env.StopRecording();
					break;
			}
		});
}

} // namespace screen
} // namespace synth
