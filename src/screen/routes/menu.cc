#include "screen/routes.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <TFT9341.h>
#include "screen/button.h"

#define SYNTH_MENU_ITEM_TYPES(V)                                               \
  V(Keyboard)                                                                  \
  V(PracticePlayerList)                                                        \
  V(Recorder)                                                                  \
  V(RecordsPlayer)                                                             \
  V(Settings)

namespace synth {
namespace screen {

#define V(TYPE) k ## TYPE,
enum class Setting {
  SYNTH_MENU_ITEM_TYPES(V)
};
#undef V

ROUTE_INIT(Menu) {
  return PaintMenu({
  	"Keyboard",
  	"Practice Player",
  	"Recorder",
  	"Records Player",
  	"Settings",
	});
}

ROUTE_TOUCH(Menu) {
  Button::IteratePressed(buttons, point,
		[&](uint8_t index) {
			switch (Setting(index)) {
#define V(TYPE)                                                              \
				case Setting::k ## TYPE:                                             \
					controller->set_route(Route::k ## TYPE);                           \
					break;
				SYNTH_MENU_ITEM_TYPES(V)
#undef V
			}
  	});
}

ROUTE_TOUCHEND(Menu) {
	Button::ClearClicks(buttons);
}

} // namespace screen
} // namespace synth
