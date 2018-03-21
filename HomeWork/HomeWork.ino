//#include <LiquidCrystal_I2C.h>

#include "DHT.h"
#include <ESP8266WiFi.h>

//#define PUMP_RLY 4    // output drive relay for pump GPIO4 (D2)
#define DHTPIN 2     // what pin we're connected to GPIO2 (D4)
#define DHTTYPE DHT22   // DHT 11
#define LED1 D5
#define LED2 D6
#define LED3 D7

DHT *dht;

void readDht(DHT *dht, float *temp, float *humid);

void setup() {
    Serial.begin(115200);
    delay(10);
    pinMode(LED1, OUTPUT); //
    pinMode(LED2, OUTPUT);
    pinMode(LED3; OUTPUT);
}

void loop() {

  // read the value from the sensor:
  Value = DHT(DHTPIN);
  // turn the ledPin on
  digitalWrite(Value>=40, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(100);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}
}
