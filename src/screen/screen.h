/** 
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "app-state.h"
#include "screen/button.h"

namespace synth {
namespace screen {

class Controller {
private:
  std::vector<Button> buttons;

public:
  inline std::vector<Button>& get_buttons() { return buttons; }

  void paint(AppState& state);
  void tap(AppState& state, uint16_t x, uint16_t y);
};

}  // namespace screen
}  // namespace synth
