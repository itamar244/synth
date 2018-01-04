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

#define PAGE_TYPES(V)                                                          \
  V(INDEX)                                                                     \
  V(KEYBOARD)

#define PAGE_SCREEN(page)                                                      \
  std::vector<Button> screen_ ## page()

#define PAGE_TOUCH(page)                                                       \
  void page_touch_ ## page(                                                    \
    Controller* controller, AppState& state, const Point& point)

#define PAGE_TOUCHEND(page)                                                    \
  void page_touchend_ ## page(                                                 \
    Controller* controller, AppState& state)

namespace synth {
namespace screen {

#define V(PAGE)                                                                \
  PAGE_SCREEN(PAGE);                                                           \
  PAGE_TOUCH(PAGE);                                                            \
  PAGE_TOUCHEND(PAGE);
  PAGE_TYPES(V)
#undef V

} // namespace screen
} // namespace synth
