#include "screen/routes.h"
#include "screen/button.h"

#define SYNTH_MENU_ITEM_TYPES(V)                                               \
	V(Player)                                                                    \
	V(PracticePlayerList)                                                        \
	V(RecordsPlayer)                                                             \
	/*(Settings)*/

namespace synth {
namespace screen {

#define V(TYPE) k ## TYPE,
enum class Setting {
	SYNTH_MENU_ITEM_TYPES(V)
};
#undef V

ROUTE_INIT(Menu) {
	return PaintMenu(window, {
		"Player",
		"Practice Player",
		"Records Player",
		"Settings",
	});
}

ROUTE_TOUCH(Menu) {
	state.IteratePressedButtons([&state](uint8_t index) {
		switch (Setting(index)) {
#define V(TYPE)                                                                \
			case Setting::k ## TYPE:                                                 \
				state.controller->set_route(Route::k ## TYPE);                         \
				break;
			SYNTH_MENU_ITEM_TYPES(V)
#undef V
		}
	});
}

} // namespace screen
} // namespace synth
