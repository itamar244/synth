#include <Arduino.h>
#include <TFT9341.h>
#include "eeprom.h"
#include "env.h"
#include "screen/routes.h"
#include "screen/screen.h"
#include "serial_communication.h"
#include "sound.h"

namespace serial = synth::serial;
namespace sound = synth::sound;
namespace eeprom = synth::eeprom;
using synth::Environment;
using ScreenController = synth::screen::Controller;
using Route = synth::screen::Route;

Environment env;
ScreenController screen_controller;

void setup() {
	Serial.begin(9600);
	sound::Init();
	eeprom::MaybeInit();

	lcd.begin();
	lcdtouch.InitTypeTouch(1);
}

void loop() {
	env.Tick();

	if (screen_controller.route() != Route::kIndex && Serial.available()) {
		serial::Receive(env);
	}
	screen_controller.Paint(env);

  if (digitalRead(2) == 0) {
    screen_controller.Touch(env);
  } else if (screen_controller.is_touched()) {
    screen_controller.Touchend(env);
  }
}
