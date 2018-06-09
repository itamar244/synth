#include "screen/routes.h"
#include "screen/routes/player_list_component.h"

namespace synth {
namespace screen {

ROUTE_INIT(Player) {
	return PlayerListInit();
}

ROUTE_TOUCH(Player) {
	Button::IteratePressed(
		buttons, point,
		PlayerListTouchHandler<MelodyPlayer>(controller, env, []() {}));
}

} // namespace screen
} // namespace synth
