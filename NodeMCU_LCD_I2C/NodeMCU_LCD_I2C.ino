/*
 * Vin – VCC
 * GND – GND
 * D1 – SCL
 * D2 – SDA
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); //ถ้าจอไม่แสดงผล ให้ลองเปลี่ยน 0x3F เป็น 0x27
void setup()
{
  lcd.begin();
  lcd.backlight(); // เปิดไฟ backlight
  lcd.setCursor(2, 0); // ไปที่ตัวอักษรที่ 2 บรรทัดที่ 0
  lcd.print("LCD ESP8266");
  lcd.setCursor(2, 1); // ไปที่ตัวอักษรที่ 3 บรรทัดที่ 1
  lcd.print("Hello World");
}

void loop()
{
}
