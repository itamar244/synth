#include "screen/routes.h"
#include "screen/routes/player_list_component.h"

namespace synth {
namespace screen {

ROUTE_INIT(Player) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(Player) {
	PlayerListTouchHandler(state, [&](auto& path) {
		state.env.SetPlayer<MelodyPlayer>(path);
	});
}

} // namespace screen
} // namespace synth
