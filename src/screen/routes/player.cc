#include "screen/routes.h"
#include "screen/routes/player_list_component.h"

namespace synth {
namespace screen {

ROUTE_INIT(Player) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(Player) {
	PlayerListTouchHandler<MelodyPlayer>(state, []() {});
}

} // namespace screen
} // namespace synth
