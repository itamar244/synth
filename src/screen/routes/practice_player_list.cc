#include "screen/routes.h"
#include "melody_player/melody_comparator.h"
#include "screen/routes/player_list_component.h"

namespace synth::screen {

ROUTE_INIT(PracticePlayerList) {
	return PlayerListInit(window);
}

ROUTE_TOUCH(PracticePlayerList) {
	PlayerListTouchHandler<MelodyPlayer>(state, [&state]() {
		state.controller->set_route(Route::kPracticePlayerPlaying);
	});
}

} // namespace synth::screen
