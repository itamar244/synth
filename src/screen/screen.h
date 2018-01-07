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

enum class Page;

class Controller {
public:
  Controller();

  inline Page page() const { return page_; }
  inline void set_page(screen::Page next) {
    page_ = next;
    is_painted_ = false;
  }

  void Paint(Environment& env);
  void Touch(Environment& env);
  void Touchend(Environment& env);

private:
  std::vector<Button> buttons_;
  Page page_;
  bool is_painted_ = false;
};

}  // namespace screen
}  // namespace synth
