#pragma once

#include "screen/screen.h"

namespace synth {


class App {
private:
  screen::Controller screen;
  
public:
  void init();
  void tick();
};

}  // namespace synth
