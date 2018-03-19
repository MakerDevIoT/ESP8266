#include <Wire.h>               // Include I2C bus library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

void setup() 
{
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void loop() 
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextSize(2);
  OLED.print("Jirawin"); // Your message
  OLED.setCursor(0,15);
  OLED.print("Deecharoenchitpong"); // Your message
  OLED.display();
}


