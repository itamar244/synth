#include <Arduino.h>
#include <TFT9341.h>
#include "screen/screen.h"
#include "song_player/songs.h"
#include "env.h"

using namespace synth;

Environment env;
screen::Controller screen_controller;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
  env.PlaySong(
    songs::SEVEN_NATION_ARMY,
    SONG_SIZE(SEVEN_NATION_ARMY));
}

void loop() {
  env.Tick();

  screen_controller.Paint(env);

  if (digitalRead(2) == 0) {
    screen_controller.Touch(env);
  } else if (screen_controller.is_touched()) {
    screen_controller.Touchend(env);
  }
}
