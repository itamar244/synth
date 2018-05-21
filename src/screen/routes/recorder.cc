#include "screen/routes.h"
#include "recorder.h"

namespace synth {
namespace screen {

ROUTE_INIT(Recorder) {
	return std::vector<Button>();
}

ROUTE_TOUCH(Recorder) {

}

ROUTE_TOUCHEND(Recorder) {  Button::ClearClicks(buttons); }

} // namespace screen
} // namespace synth
