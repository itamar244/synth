#pragma once

#include "env.h"
#include "screen/screen.h"

namespace synth {

class App {
private:
  screen::Controller screen_;
  Environment env_;
  bool screen_pressed_ = false;

public:
  void init();
  void tick();
};

}  // namespace synth
