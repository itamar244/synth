#include <Arduino.h>
#include "app.h"

synth::App app;

void setup() {
  Serial.begin(9600);
  app.init();
}

void loop() {
  app.tick();
}
