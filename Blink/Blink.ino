#include <Arduino.h> // For Atom Editor

void setup() {
  // ESP8266 Pin 16, ESP32 Pin13
  pinMode(16, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
