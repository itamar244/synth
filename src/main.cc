#include <Arduino.h>
#include <TFT9341.h>
#include "env.h"
#include "screen/routes.h"
#include "screen/screen.h"
#include "serial_communication.h"

using synth::Environment;
using ScreenController = synth::screen::Controller;
using Route = synth::screen::Route;

Environment env;
ScreenController screen_controller;

void setup() {
	Serial.begin(9600);
	lcd.begin();
	lcdtouch.InitTypeTouch(1);
}

void loop() {
	env.Tick();

	if (screen_controller.route() != Route::kIndex && Serial.available()) {
		HandleSerialCommunication(env);
	}
	screen_controller.Paint(env);

  if (digitalRead(2) == 0) {
    screen_controller.Touch(env);
  } else if (screen_controller.is_touched()) {
    screen_controller.Touchend(env);
  }
}
