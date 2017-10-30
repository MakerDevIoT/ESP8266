#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1); 
int x;
void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC,0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
}
void loop(){
  OLED.clearDisplay(); 
  OLED.setTextColor(WHITE,BLACK);   //Text is white ,background is black
  OLED.setCursor(0, 0);
  OLED.setTextSize(2); 
  OLED.println("IOT");
  OLED.setTextSize(1);    
  OLED.print("Laboratory");
  OLED.println(" 2016");
  OLED.setTextColor(BLACK,WHITE); // 'inverted' text
  OLED.print("www.praphas.com");
  OLED.setTextColor(WHITE,BLACK); // 'inverted' text again
  OLED.setCursor(60,0);
  OLED.setTextSize(2);  
  OLED.println(x,DEC); 
  OLED.display(); 
  x++;
  delay(250); 
}
