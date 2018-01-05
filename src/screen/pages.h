/**
 * responsible for screen painting and touch responses.
 * page_paint_<PAGE> and page_touch<TYPE>_<PAGE> are generated and are being used
 * in "screen/screen.cc".
 * each PAGE is implemented in `screen/pages/PAGE.cc`.
 */
#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "app-state.h"
#include "screen/button.h"

#define PAGE_TYPES(V)                                                          \
  V(INDEX)                                                                     \
  V(KEYBOARD)

#define PAGE_PAINT(PAGE)                                                       \
  std::vector<Button> page_paint_ ## PAGE()

#define PAGE_TOUCH(PAGE)                                                       \
  void page_touch_ ## PAGE(                                                    \
    std::vector<Button>& buttons, AppState& state, const Point& point)

#define PAGE_TOUCHEND(PAGE)                                                    \
  void page_touchend_ ## PAGE(                                                 \
    std::vector<Button>& buttons, AppState& state)

namespace synth {

namespace screen {
enum class Page {
#define V(PAGE) PAGE,
PAGE_TYPES(V)
#undef V
};

#define V(PAGE)                                                                \
  PAGE_PAINT(PAGE);                                                            \
  PAGE_TOUCH(PAGE);                                                            \
  PAGE_TOUCHEND(PAGE);
  PAGE_TYPES(V)
#undef V

} // namespace screen
} // namespace synth
