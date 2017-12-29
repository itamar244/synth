#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "screen/button.h"
// #include "screen/screen.h"
// not included because it will cause circular reference and many issues

#define PAGE_SCREEN(page) std::vector<Button> screen_ ## page()
#define PAGE_TAP(page) \
  void tap_ ## page(uint16_t x, uint16_t y, Controller* controller)

namespace synth {
namespace screen {

class Controller; // forward declare Controller

enum class Page {
  INDEX,
  KEYBOARD,
};

PAGE_SCREEN(INDEX);
PAGE_TAP(INDEX);

PAGE_SCREEN(KEYBOARD);
PAGE_TAP(KEYBOARD);

} // namespace screen
} // namespace synth
