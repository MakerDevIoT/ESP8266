#include <DHT.h>

#include <DHT.h>                // Include DHT sensor library
#include <Wire.h>               // Include I2C bus library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

#define DHTTYPE DHT22           // Define type of sensor 
#define DHTPIN  D4              // Define connected pin
 
DHT dht(DHTPIN, DHTTYPE, 15);   // Initial DHT sensor

void setup() 
{
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void loop() 
{
  float humid = dht.readHumidity();     // Read humidity data
  float temp = dht.readTemperature();   // Read temperature data

  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextSize(2);
  OLED.print(humid + String("%"));
  OLED.setCursor(0,15);
  OLED.print(temp + String("C"));
  OLED.write(247);
  OLED.display();
  delay(1000);
}


