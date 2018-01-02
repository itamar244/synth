/**
 * responsible for screen painting and tap responses.
 * screen_<PAGE_NAME> and tap_<PAGE_NAME> are generated and are being used
 * in "screen/screen.cpp"
 */
#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "app-state.h"
#include "screen/button.h"
#include "screen/screen.h"

#define PAGE_SCREEN(page)                                                      \
  std::vector<Button> screen_ ## page()
#define PAGE_TAP(page)                                                         \
  void tap_ ## page(Controller* controller, AppState& state, const Point& point)

namespace synth {
namespace screen {

PAGE_SCREEN(INDEX);
PAGE_TAP(INDEX);

PAGE_SCREEN(KEYBOARD);
PAGE_TAP(KEYBOARD);

} // namespace screen
} // namespace synth
