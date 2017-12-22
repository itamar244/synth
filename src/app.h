#pragma once

#include "screen.h"

namespace synth {

class App {
private:
  Screen screen;
  
public:
  void init();
  void tick();
};

}  // namespace synth
