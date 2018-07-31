#include "../routes.h"
#include "player_list_component.h"

namespace synth {
namespace screen {

ROUTE_INIT(Player) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(Player) {
	Button::IteratePressed(
		buttons, point,
		PlayerListTouchHandler<MelodyPlayer>(controller, env, []() {}));
}

} // namespace screen
} // namespace synth
