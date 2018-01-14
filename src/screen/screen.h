/**
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <StandardCplusplus.h>
#include <vector>
#include "env.h"
#include "screen/button.h"

namespace synth {
namespace screen {

enum class Route;

class Controller {
public:
  Controller();

	inline bool is_touched() const { return is_touched_; }
  inline Route route() const { return route_; }
  inline void set_route(Route next) {
    route_ = next;
    is_painted_ = false;
  }

  void Paint(Environment& env);
  void Touch(Environment& env);
  void Touchend(Environment& env);

private:
  std::vector<Button> buttons_;
  Route route_;
  bool is_painted_ = false, is_touched_ = false;
};

}  // namespace screen
}  // namespace synth
