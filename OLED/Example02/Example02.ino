#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(4); 
int x;
void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC,0x3C); //initialize I2C addr 0x3c
}
void loop(){
  OLED.clearDisplay(); 
  OLED.setTextColor(WHITE,BLACK);
  OLED.drawRect(10,10, 100,40,WHITE);
  OLED.drawLine(0, 63, 127, 0, WHITE);
  OLED.drawCircle(110, 50, 12, WHITE);
  OLED.fillCircle(45, 50, 8, WHITE);
  OLED.drawTriangle(70, 60, 90, 60, 80, 46, WHITE);
  OLED.fillRect(15,15,20,20,WHITE);
  OLED.fillRoundRect(50,15,50,20,10,WHITE);
  OLED.setCursor(5,30);
  OLED.setTextSize(1); 
  OLED.println("www.praphas.com");
  OLED.display(); //
  delay(250); 
}
