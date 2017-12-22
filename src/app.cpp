#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::init() {
  lcd.begin(0);
  lcdtouch.InitTypeTouch(2);
}

void App::tick() {
  screen.paint();
  if (digitalRead(2) == 0) {
    lcdtouch.readxy();
    const uint16_t x = lcdtouch.readx(), y = lcdtouch.ready();
    screen.tap(x, y);
  }
}

}  // namespace synth
