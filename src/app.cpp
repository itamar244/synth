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
    lcdtouch.readxy();
    const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();
    screen_.tap(
      state_, 
      static_cast<uint16_t>((WIDTH - x - 80) * 1.3), 
      (y - 13) / 1.3
    );
  }
}

} // namespace synth
