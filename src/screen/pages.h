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
#include "env.h"
#include "screen/button.h"
#include "screen/screen.h"

#define PAGE_TYPES(V)                                                          \
  V(Index)                                                                     \
  V(Keyboard)                                                                  \
  V(Settings)

#define WRAPPED_PAGE_TYPES(WRAPPER, V)                                         \
  WRAPPER(V, Index)                                                            \
  WRAPPER(V, Keyboard)                                                         \
  WRAPPER(V, Settings)

#define PAGE_PAINT(PAGE)                                                       \
  std::vector<Button> PagePaint ## PAGE()

#define PAGE_TOUCH(PAGE)                                                       \
  void PageTouch ## PAGE(                                                      \
    Controller* controller, std::vector<Button>& buttons,                      \
    Environment& env, const Point& point)

#define PAGE_TOUCHEND(PAGE)                                                    \
  void PageTouchend ## PAGE(                                                   \
    std::vector<Button>& buttons, Environment& env)

namespace synth {
namespace screen {

enum class Page {
#define V(PAGE) k ## PAGE,
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
