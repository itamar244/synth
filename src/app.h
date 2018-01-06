#pragma once

#include "env.h"
#include "screen/screen.h"

namespace synth {

class App {
public:
  void Init();
  void Tick();

private:
  Environment env_;
  screen::Controller screen_;
  bool screen_pressed_ = false;
};

}  // namespace synth
