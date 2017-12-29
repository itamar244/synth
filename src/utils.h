#pragma once

namespace synth {
namespace utils {

class Point {
public:
  uint16_t x, y;
};

class Button: public Point {
public:
  int16_t width, height;
  
  Button(uint16_t x, uint16_t y, int16_t width, int16_t height)
    : Point{x, y}
    , width(width)
    , height(height) {}

  inline bool is_clicked(uint16_t given_x, uint16_t given_y) const {
    const int diff_x = given_x - x, diff_y = given_y - y;

    return diff_x < width && diff_x > 0 && diff_y < height && diff_y > 0;
  }
};

}  // namespace utils
}  // namespace synth
