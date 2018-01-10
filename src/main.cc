#include <Arduino.h>
#include <TFT9341.h>
#include "env.h"
#include "screen/pages.h"
#include "screen/screen.h"
#include "serial_communication.h"

using synth::Environment;
using ScreenController = synth::screen::Controller;
using Page = synth::screen::Page;

Environment env;
ScreenController screen_controller;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcdtouch.InitTypeTouch(1);
}

void loop() {
  env.Tick();

	if (screen_controller.page() != Page::kIndex && Serial.available()) {
		HandleSerialCommunication(env);
	}
	screen_controller.Paint(env);

  if (digitalRead(2) == 0) {
    screen_controller.Touch(env);
  } else if (screen_controller.is_touched()) {
    screen_controller.Touchend(env);
  }
}
