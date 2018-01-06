#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::Init() {
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void App::Tick() {
  env_.Tick();

  screen_.Paint(env_);
  
  if (digitalRead(2) == 0) {
    screen_pressed_ = true;
    screen_.Touch(env_);
  } else if (screen_pressed_) {
    screen_pressed_ = false;
    screen_.Touchend(env_);
  }
}

} // namespace synth
