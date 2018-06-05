#include "screen/routes.h"
#include "screen/button.h"

namespace synth {
namespace screen {

ROUTE_INIT(Settings) {
  return PaintMenu({
  	"Back",
  	"Audio",
	});
}

ROUTE_TOUCH(Settings) {
  Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			switch (index) {
				case 0: // "Back"
					controller->set_route(Route::kMenu);
					break;
				case 1: // "Audio"
					env.SetAudioType(
						env.audio()->Type() == Audio::kBuiltin
							? Audio::kSerialPort : Audio::kBuiltin);
					break;
			}
  	});
}

} // namespace screen
} // namespace synth
