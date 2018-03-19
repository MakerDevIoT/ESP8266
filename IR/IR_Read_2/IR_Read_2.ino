#include <IRremote.h>
#include <avr/interrupt.h>
 
int RECV_PIN = 5;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
int on = 0;
unsigned long last = millis();
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Hello");
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
