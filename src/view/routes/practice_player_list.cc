#include "view/routes.h"
#include "melody_player/melody_comparator.h"
#include "view/routes/player_list_component.h"

namespace synth::view {

ROUTE_INIT(PracticePlayerList) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(PracticePlayerList) {
	PlayerListTouchHandler(state, [&state](auto& path) {
		state.env.SetPlayer<MelodyPlayer>(path);
		state.controller->set_route(Route::kPracticePlayerPlaying);
	});
}

} // namespace synth::view
