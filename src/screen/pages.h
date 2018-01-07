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

#define PAGE_TYPES(V)                                                          \
  V(INDEX)                                                                     \
  V(KEYBOARD)                                                                  \
  V(SETTINGS)

#define WRAPPED_PAGE_TYPES(WRAPPER, V)                                         \
  WRAPPER(V, INDEX)                                                            \
  WRAPPER(V, KEYBOARD)                                                        \
  WRAPPER(V, SETTINGS)

#define PAGE_PAINT(PAGE)                                                       \
  std::vector<Button> PagePaint_ ## PAGE()

#define PAGE_TOUCH(PAGE)                                                       \
  void PageTouch_ ## PAGE(                                                    \
    std::vector<Button>& buttons, Environment& env, const Point& point)

#define PAGE_TOUCHEND(PAGE)                                                    \
  void PageTouchend_ ## PAGE(                                                 \
    std::vector<Button>& buttons, Environment& env)

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
