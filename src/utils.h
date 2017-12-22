#pragma once

#include <Arduino.h>

namespace synth {
namespace utils {

struct Point {
  int16_t x, y;
};

struct Button: public Point {
  int16_t width, height;
  String text;
  
  Button(int16_t x, int16_t y, int16_t width, int16_t height, String text)
    : Point{x, y}
    , width{width}
    , height{height}
    , text{text} {}
};

}  // namespace utils
}  // namespace synth
