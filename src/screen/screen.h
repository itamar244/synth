/** 
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "env.h"
#include "screen/button.h"
#include "screen/point.h"

namespace synth {
namespace screen {

class Controller {
private:
  std::vector<Button> buttons_;

public:
  inline std::vector<Button>& get_buttons() { return buttons_; }

  void paint(Environment& env);
  void touch(Environment& env);
  void touchend(Environment& env);
};

}  // namespace screen
}  // namespace synth
