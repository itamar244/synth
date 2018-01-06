/** 
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <vector>
#include "env.h"
#include "screen/button.h"

namespace synth {
namespace screen {

class Controller {
public:
  inline std::vector<Button>& buttons() { return buttons_; }

  void Paint(Environment& env);
  void Touch(Environment& env);
  void Touchend(Environment& env);

private:
  std::vector<Button> buttons_;
};

}  // namespace screen
}  // namespace synth
