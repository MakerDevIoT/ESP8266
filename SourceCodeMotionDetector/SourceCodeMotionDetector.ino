/*.*************************************************************
 * IoT Motion Detector with Blynk
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * Developed by Marcelo Rovai - 30 November 2016
 **************************************************************/
#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
char auth[] = "ab688ab0efd24112b5087d6e572b8fbf";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT KMUTNB_1";
char pass[] = "kmutnb2018";


/* HC-SR501 Motion Detector */
#define ledPin D7 
#define pirPin D4 // Input for HC-S501
int pirValue=0; // Place to store read PIR Value
int motionDetected = 0;
void getPirValue(void);
void setup()
{
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop()
{
  getPirValue();
  Blynk.run();
}

/***************************************************
 * Get PIR data
 **************************************************/
void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println(pirValue);
    //Serial.println("==> Motion detected");
    Blynk.notify("T==> Motion detected");  //ข้อความแสดงเวลาตรวจพบความเคลื่อนไหว
  }
  
  digitalWrite(ledPin, pirValue);
}


