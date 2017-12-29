#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "utils.h"

namespace synth {

using utils::Button;
using std::vector;

enum class Page {
  INDEX,
  KEYBOARD,
};

class Screen {
private:
  vector<Button> buttons;
  Page current_page = Page::INDEX;
  bool painted = false;

public:
  const inline vector<Button>& get_buttons() { return buttons; }

  void paint();
  void tap(uint16_t x, uint16_t y);
  void switch_page(Page to);
};

}  // namespace synth
