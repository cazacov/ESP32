#include <Arduino.h>

int delayTime = 1000;

int LED_BUILTIN = 1;
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayTime);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayTime);
}