#include <Arduino.h>
#include "app.h"

synth::App app;

void setup() {
  Serial.begin(9600);
  app.Init();
}

void loop() {
  app.Tick();
}
