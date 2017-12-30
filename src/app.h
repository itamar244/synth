#pragma once

#include "app-state.h"
#include "screen/screen.h"

namespace synth {

class App {
private:
  AppState state;
  screen::Controller screen;
  
public:
  void init();
  void tick();
};

}  // namespace synth
