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
  inline std::vector<Button>& get_buttons() { return buttons_; }

  void paint(Environment& env);
  void touch(Environment& env);
  void touchend(Environment& env);

private:
  std::vector<Button> buttons_;
};

}  // namespace screen
}  // namespace synth
