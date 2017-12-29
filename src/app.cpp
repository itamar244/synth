#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::init() {
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void App::tick() {
  screen.paint();
  if (digitalRead(2) == 0) {
    lcdtouch.readxy();
    const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();
    screen.tap(WIDTH - x, y);
  }
}

}  // namespace synth
