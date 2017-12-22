#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "utils.h"

namespace synth {

using utils::Button;

class Screen {
private:
  std::vector<Button> buttons;
  uint8_t screen_index = 0;
  bool painted = false;

public:
  void paint();
  void tap(uint16_t x, uint16_t y);
  void switch_screen();
};

}  // namespace synth
