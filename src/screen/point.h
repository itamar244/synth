#pragma once

#include <cstdint>

namespace synth::screen {

struct Point {
  float x, y;

  Point(float x, float y)
    : x(x), y(y) {}

  template<class X, class Y>
  Point(X x, Y y)
    : x(static_cast<float>(x))
    , y(static_cast<float>(y)) {}
};

}  // namespace synth::screen
