#pragma once

#include <Arduino.h>
#include "screen/point.h"

namespace synth {
namespace screen {

struct Button: public Point {
  uint8_t width, height;
  bool is_pressed = false;

  Button(uint16_t x, uint16_t y, uint8_t width, uint8_t height)
    : Point(x, y), width(width), height(height) {}

  inline bool IsTapped(const Point& point) const {
    const int16_t diff_x = point.x - x, diff_y = point.y - y;

    return diff_x < width && diff_x > 0 && diff_y < height && diff_y > 0;
  }
};

}  // namespace screen
}  // namespace synth
