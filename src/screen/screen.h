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
#include "screen/point.h"

namespace synth {
namespace screen {

Point get_clicked_point();

class Controller {
private:
  std::vector<Button> buttons_;

public:
  inline std::vector<Button>& get_buttons() { return buttons_; }

  void paint(AppState& state);
  void tap(AppState& state);
};

}  // namespace screen
}  // namespace synth
