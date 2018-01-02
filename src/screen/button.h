#pragma once

#include <Arduino.h>
#include "screen/point.h"

namespace synth {
namespace screen {

struct Button: public Point {
  int16_t width, height;
  bool is_pressed = false;

  Button(uint16_t x, uint16_t y, int16_t width, int16_t height)
    : Point(x, y), width(width), height(height) {}

  inline bool is_tapped(uint16_t given_x, uint16_t given_y) const {
    const int diff_x = given_x - x, diff_y = given_y - y;

    return diff_x < width && diff_x > 0 && diff_y < height && diff_y > 0;
  }

  inline bool is_tapped(Point point) const { 
    return is_tapped(point.x, point.y);
  }
};

}  // namespace screen
}  // namespace synth
