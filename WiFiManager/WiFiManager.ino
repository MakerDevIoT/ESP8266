#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

int LEDpin = D0 ;
int SWpin = D7;

void setup()
{
pinMode (LEDpin, OUTPUT);
pinMode (SWpin, INPUT_PULLUP);
Serial.begin(115200);
WiFiManager wifiManager;
if(!digitalRead(SWpin))
{
wifiManager.resetSettings();
}
wifiManager.autoConnect("Jirawin2");   //แก้ไขเป็นชื่อตัวเอง จะได้รู้ว่าเป็นของใคร
Serial.println("Connect Success ^_^ ");
digitalWrite(LEDpin, HIGH);

}
void loop()
{
//
}
