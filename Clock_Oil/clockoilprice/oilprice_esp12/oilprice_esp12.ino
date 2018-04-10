#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <time.h>
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "Wire.h"
#include "OilFonts.h"
#include "OilImages.h"

// WIFI
const char* WIFI_SSID = "IT";
const char* WIFI_PWD = "mailmail";

//Time
int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;

//Oil Price
float gas95 = 0.0;
float LocalCharge = 2.36;
String price1;
String price2;
unsigned long previousMillis;

// Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D4;
const int SDC_PIN = D3;

SSD1306Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
OLEDDisplayUi   ui( &display );

void drawProgress(OLEDDisplay *display, int percentage, String label);
void updateData(OLEDDisplay *display);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  //Set VCC & GND PIN
  pinMode(D2, OUTPUT); digitalWrite(D2, 1); // vcc
  pinMode(D1, OUTPUT); digitalWrite(D1, 0);  // gnd
  
  // initialize dispaly
  display.init();
  display.clear();
  display.display();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setContrast(255);

  WiFi.begin(WIFI_SSID, WIFI_PWD);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.clear();
    display.drawXbm(10, 0, 105, 48, PTT_Logo_bits);
    display.drawXbm(46, 50, 8, 8, counter % 3 == 0 ? activeSymbole : inactiveSymbole);
    display.drawXbm(60, 50, 8, 8, counter % 3 == 1 ? activeSymbole : inactiveSymbole);
    display.drawXbm(74, 50, 8, 8, counter % 3 == 2 ? activeSymbole : inactiveSymbole);
    display.display();

    counter++;
  }

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }

  updateData(&display);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1800000) {
    updateData(&display);
  }

  drawOilprice();
}

void drawProgress(OLEDDisplay *display, int percentage, String label) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(2, 28, 124, 10, percentage);
  display->display();
}

void updateData(OLEDDisplay *display) {
  drawProgress(display, 10, "Updating Oilprice...");
  updateAnto();
  drawProgress(display, 100, "Updating Oilprice Done");
  delay(1000);
}

void drawOilprice() {
  unsigned long curTime = millis();
  int dots = (curTime % 1000) < 500;
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  if ((newtime->tm_hour) < 10) tmpNow += "0";
  tmpNow += String(newtime->tm_hour);
  if (dots) tmpNow += ":"; else tmpNow += " ";
  if ((newtime->tm_min) < 10) tmpNow += "0";
  tmpNow += String(newtime->tm_min);
  tmpNow += "     ";

  if ((newtime->tm_mday) < 10) tmpNow += "0";
  tmpNow += String(newtime->tm_mday);
  tmpNow += "/";
  if ((newtime->tm_mon + 1) < 10) tmpNow += "0";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "/";
  String tmpYear = String(newtime->tm_year + 2443);
  tmpNow += tmpYear.substring(2, 6);

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Dialog_plain_50);
  display.drawString(0, -8, price1);  //30
  display.setFont(ArialMT_Plain_24);
  display.drawString(60, 18, price2);  //.41
  display.setFont(ArialMT_Plain_16);
  display.drawString(5, 45, tmpNow);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(130, 30, "Bath/L");
  display.setFont(ArialMT_Plain_16);
  display.drawString(128, 0, "GAS 95");
  display.display();
}

void updateAnto() {
  HTTPClient http;
  http.begin("http://api.anto.io/request/antokey/gas.95e10.price");
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    payload = payload.substring(26, 31);
    gas95 = payload.toFloat();
    gas95 = gas95 + LocalCharge;
    int price3 = (int)(gas95);
    price2 = String(gas95);
    price1 = String(price3);
    price2 = price2.substring(2, 5);
    Serial.println(price1);
    Serial.println(price2);
  }
  http.end();
  previousMillis = millis();
}
