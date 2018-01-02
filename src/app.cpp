#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::init() {
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void App::tick() {
  screen_.paint(state_);
  if (digitalRead(2) == 0) {
    screen_.tap(state_);
  }
}

} // namespace synth
