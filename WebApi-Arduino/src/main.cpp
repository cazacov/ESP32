#include <Arduino.h>

#define LED 23


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

int counter = 0;

void loop() {
  // put your main code here, to run repeatedly:
  counter++;
  digitalWrite(LED, HIGH);
  Serial.println("High");
  delay(2000);
  digitalWrite(LED, LOW);
  Serial.println("Low");
  delay(2000);
}
