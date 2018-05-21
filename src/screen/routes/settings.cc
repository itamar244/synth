#include "screen/routes.h"
#include <Arduino.h>
#include <TFT9341.h>
#include "screen/button.h"

#define BUTTON_ITEMS 2
#define SYNTH_SETTING_TYPES(V)                                                 \
  V(Back)                                                                      \
  V(Audio)

namespace synth {
namespace screen {

#define V(TYPE) #TYPE,
const char* kSettingsButtonNames[BUTTON_ITEMS] = {
  SYNTH_SETTING_TYPES(V)
};
#undef V

#define V(TYPE) k ## TYPE,
enum Setting {
  SYNTH_SETTING_TYPES(V)
};
#undef V

ROUTE_INIT(Settings) {
#define V(TYPE) #TYPE,
  return PaintMenu({
  	SYNTH_SETTING_TYPES(V)
	});
#undef V
}

ROUTE_TOUCH(Settings) {
  Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			switch (index) {
				case kBack:
					controller->set_route(Route::kMenu);
					break;
				case kAudio:
					env.SetAudioType(
						env.audio()->IsType(Audio::kBuiltin)
							? Audio::kSerialPort : Audio::kBuiltin);
					break;
			}
  	});
}

ROUTE_TOUCHEND(Settings) {
  Button::ClearClicks(buttons);
}

} // namespace screen
} // namespace synth
