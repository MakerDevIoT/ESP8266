// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN D4 // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE DHT11 // DHT 11 
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

#include <ESP8266WiFi.h>
#include <IoTtweet.h>

const char *userid = "002031"; //IoTtweet account user ID (6 digits, included zero pre-fix)
const char *key = "9bootw4afzrc"; //IoTtweet registered device key in "MY IOT Garage"
const char *ssid = "IOT KMUTNB_1"; //Your-WiFi-router-SSID
const char *password = "kmutnb2018"; //Your-WiFi-password

float data0, data1, data2, data3; //Your sending data variable.
String private_tweet = "สวัสดีครับ"; //Your private tweet meassage to dashboard กดเลือก Tweet privaet panel
String public_tweet = "IoT Smart Farm 4.0"; //Your public tweet message to dashboard กดเลือก Tweet public panel // แก้ไขชื่อได้

IoTtweet myiot; //naming your devices

void setup() {
Serial.begin(9600); 
// Initialize device.
dht.begin();
Serial.println("DHTxx Unified Sensor Example");
// Print temperature sensor details.
sensor_t sensor;
dht.temperature().getSensor(&sensor);
Serial.println("------------------------------------");
Serial.println("Temperature");
Serial.print ("Sensor: "); Serial.println(sensor.name);
Serial.print ("Driver Ver: "); Serial.println(sensor.version);
Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println(" *C");
Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println(" *C");
Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println(" *C"); 
Serial.println("------------------------------------");
// Print humidity sensor details.
dht.humidity().getSensor(&sensor);
Serial.println("------------------------------------");
Serial.println("Humidity");
Serial.print ("Sensor: "); Serial.println(sensor.name);
Serial.print ("Driver Ver: "); Serial.println(sensor.version);
Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println("%");
Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println("%");
Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println("%"); 
Serial.println("------------------------------------");
// Set delay between sensor readings based on sensor details.
delayMS = sensor.min_delay / 1000;

String libvers = myiot.getVersion();
Serial.println("IoTtweet Library vesion : " + String(libvers));

//Connect WiFi
Serial.println("\nConnect wifi...");
bool conn = myiot.begin(ssid,password);

if(!conn)
{
Serial.println("WiFi connection failed.");
}else
{
Serial.println("WiFi connected !");
}


}

void loop() {
// Delay between measurements.
delay(delayMS);
// Get temperature event and print its value.
sensors_event_t event; 
dht.temperature().getEvent(&event);
if (isnan(event.temperature)) {
Serial.println("Error reading temperature!");
}
else {
Serial.print("Temperature: ");
Serial.print(event.temperature);
Serial.println(" *C");
data0 = event.temperature ; //อุณหภมิ
}
// Get humidity event and print its value.
dht.humidity().getEvent(&event);
if (isnan(event.relative_humidity)) {
Serial.println("Error reading humidity!");
}
else {
Serial.print("Humidity: ");
Serial.print(event.relative_humidity);
Serial.println("%");
data1 = event.relative_humidity;
}

//Example data generating


data2 = random(50,100);
data3 = random(100,1000);

//Send data from your iot to Dashboard
String response = myiot.WriteDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
Serial.println(response); //Show response JSON from www.iottweet.com

//Waiting storage data on IoTtweet cloud 15 sec.
delay(15000);


}
