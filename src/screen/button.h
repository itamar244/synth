#pragma once

#include <Arduino.h>
#include "screen/point.h"

namespace synth {
namespace screen {

struct Button : public Point {
  uint8_t width, height;
  bool is_pressed = false;

  Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : Point(x, y), width(width), height(height) {}

  inline bool IsTapped(const Point& point) const {
    const int16_t diff_x = point.x - x, diff_y = point.y - y;

    return diff_x < width && diff_x > 0 && diff_y < height && diff_y > 0;
  }

	// button's helpers
	static inline void ClearClicks(std::vector<Button>& buttons) {
		for (auto& button : buttons) {
			if (button.is_pressed) {
				button.is_pressed = false;
			}
		}
	}

	template<class Cb>
	static void IteratePressed(
			std::vector<Button>& buttons,
			const Point& point,
			const Cb& callback) {
		for (unsigned i = 0; i < buttons.size(); i++) {
			Button& button = buttons[i];

			if (button.IsTapped(point)) {
				if (!button.is_pressed) {
					button.is_pressed = true;
					callback(i);
				}
				return;
			}
		}
	}

	template<class Cb>
	static void IterateUnpressed(
			std::vector<Button>& buttons,
			const Cb& callback) {
		for (unsigned i = 0; i < buttons.size(); i++) {
			Button& button = buttons[i];

			if (button.is_pressed) {
				button.is_pressed = false;
				callback(i);
			}
		}
	}
};

}  // namespace screen
}  // namespace synth
