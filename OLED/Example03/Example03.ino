#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>  //include font MonoBold size 9pt7b
Adafruit_SSD1306 OLED(-1); 
void setup() {
  OLED.setFont(&FreeMonoBold9pt7b); // Use font from file include   
  OLED.begin(SSD1306_SWITCHCAPVCC,0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
}
void loop(){
  OLED.clearDisplay(); 
  OLED.setTextColor(WHITE,BLACK);   //Text is white ,background is black
  OLED.setCursor(0,20);
  OLED.setTextSize(1); 
  OLED.println("Change font");
  OLED.setCursor(0,50);    
  OLED.print("OLED 128x64");
  OLED.display(); //
  delay(250); 
}
