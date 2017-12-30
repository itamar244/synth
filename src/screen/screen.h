/** 
 * the main logic of the screen module.
 * Controller is the screen controller
 */
#pragma once

#include <Arduino.h>
#include "app-state.h"
#include "screen/button.h"

namespace synth {
namespace screen {

class Controller {
private:
  Button* buttons = nullptr;
  int buttons_size = 0;

public:
  ~Controller();

  const inline Button* get_buttons() const{ return buttons; }
  const inline void set_buttons(Button* buttons, int buttons_size) {
    if (buttons != nullptr) delete buttons;
    this->buttons = buttons;
    this->buttons_size = buttons_size;
  }

  void paint(AppState& state);
  void tap(AppState& state, uint16_t x, uint16_t y);
};

}  // namespace screen
}  // namespace synth
