#include "app.h"
#include <Arduino.h>
#include <TFT9341.h>

namespace synth {

void App::init() {
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void App::tick() {
  env_.tick();

  screen_.paint(env_);
  
  if (digitalRead(2) == 0) {
    screen_pressed_ = true;
    screen_.touch(env_);
  } else if (screen_pressed_) {
    screen_pressed_ = false;
    screen_.touchend(env_);
  }
}

} // namespace synth
