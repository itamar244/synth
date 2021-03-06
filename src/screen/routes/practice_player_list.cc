#include "screen/routes.h"
#include "screen/routes/player_list_component.h"

namespace synth {
namespace screen {

ROUTE_INIT(PracticePlayerList) {
	return PlayerListInit();
}

ROUTE_TOUCH(PracticePlayerList) {
	Button::IteratePressed(
		buttons, point,
		PlayerListTouchHandler<MelodyComparator>(
			controller, env,
			[&controller]() {
				controller->set_route(Route::kPracticePlayerPlaying);
			}));
}

} // namespace screen
} // namespace synth
