#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <IRremoteESP8266.h>

 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
 
//decode_results results;

int IRrecv = 14; // choose pin for the LED
int decode_results = 5; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status 
void setup() 
 
//int on = 0;
//unsigned long last = millis();
 
//void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Hello");
}
{ 
   pinMode(decode_results, OUTPUT); // declare LED as output 
   pinMode(IRrecv, INPUT); // declare Infrared sensor as input
} 

 
void loop() {
 
  if (irrecv.decode(&results)) {  
    if (millis() - last > 50) {
      if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) 
         Serial.println(results.value, HEX);
      irrecv.resume(); // Receive the next value  
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}
