#pragma once

#include "app-state.h"
#include "screen/screen.h"

namespace synth {

class App {
private:
  AppState state_;
  screen::Controller screen_;
  
public:
  void init();
  void tick();
};

}  // namespace synth
