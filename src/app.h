#pragma once

#include "env.h"
#include "screen/screen.h"

namespace synth {

class App {
private:
  Environment env_;
  screen::Controller screen_;
  bool screen_pressed_ = false;

public:
  void init();
  void tick();
};

}  // namespace synth
