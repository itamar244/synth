#include "view/routes.h"
#include "view/routes/player_list_component.h"

namespace synth::view {

ROUTE_INIT(Player) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(Player) {
	PlayerListTouchHandler(state, [&](auto& path) {
		state.env.SetPlayer<MelodyPlayer>(path);
	});
}

} // namespace synth::view
