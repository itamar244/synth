#include <Arduino.h>
#include "app.h"

synth::App app;

void setup() {
  Serial.begin(9600);
  Serial.println(sizeof(app));
  app.init();
}

void loop() {
  app.tick();
}
