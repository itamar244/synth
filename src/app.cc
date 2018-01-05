#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::init() {
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void App::tick() {
  if (state_.audio()->type() == AudioType::BUILTIN) {
    state_.audio()->play();
  }

  screen_.paint(state_);
  
  if (digitalRead(2) == 0) {
    screen_pressed_ = true;
    screen_.touch(state_);
  } else if (screen_pressed_) {
    screen_pressed_ = false;
    screen_.touchend(state_);
  }
}

} // namespace synth
