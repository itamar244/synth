#pragma once

#include "app-state.h"
#include "screen/screen.h"

namespace synth {

class App {
private:
  screen::Controller screen_;
  AppState state_;
  bool screen_pressed_ = false;

public:
  void init();
  void tick();
};

}  // namespace synth
