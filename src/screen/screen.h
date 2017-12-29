#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "screen/pages.h"
#include "screen/button.h"

namespace synth {
namespace screen {

class Controller {
private:
  std::vector<Button> buttons;
  Page current_page = Page::INDEX;
  bool painted = false;

public:
  const inline std::vector<Button>& get_buttons() { return buttons; }

  void paint();
  void tap(uint16_t x, uint16_t y);
  void switch_page(Page to);
};

}  // namespace screen
}  // namespace synth
