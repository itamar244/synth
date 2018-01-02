#pragma once

#include <Arduino.h>

namespace synth {
namespace screen {

struct Point {
  uint16_t x, y;

  Point(uint16_t x, uint16_t y)
    : x(x), y(y) {}

  template<class X, class Y>
  Point(X x, Y y)
    : x(static_cast<uint16_t>(x))
    , y(static_cast<uint16_t>(y)) {}
};

}  // namespace screen
}  // namespace synth
