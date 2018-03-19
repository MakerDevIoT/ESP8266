#include <IRremote.h>
 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
#define OUTPUT_COUNT 4
 
unsigned long last = millis();
 
long remote_key[]={0xFD08F7,0xFD8877,0xFD48B7,0xFD28D7};
 
const byte outputPins[OUTPUT_COUNT] = {2, 3, 4, 5};
 
struct keypad {
  boolean state;
};
 
keypad output[OUTPUT_COUNT];
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Hello");
 
  for (int i=0;i<OUTPUT_COUNT;i++) {
       pinMode(outputPins[i], OUTPUT);
       output[i].state = LOW;
   }
}
 
void loop() {
    unsigned long currentMillis = millis();
    if (irrecv.decode(&results)) {
         if (currentMillis - last > 50) {
 
        //Serial.println(results.value, HEX);
 
         if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) {
            for (int val=0;val<OUTPUT_COUNT;val++) {       
                if ( results.value == remote_key[val] )  {
 
                    if (output[val].state==LOW) {
                        Serial.print ("ch[");
                        Serial.print(val);
                        Serial.println("] ON");
                        output[val].state=HIGH;
                    } else {                      
                        output[val].state=LOW;
                        Serial.print ("ch[");
                        Serial.print(val);
                        Serial.println("] OFF");                        
                    }
 
                }       
            }
         }
 
         for (int i=0;i<OUTPUT_COUNT;i++)
             digitalWrite(outputPins[i], output[i].state);
 
         }
 
      last = currentMillis;      
      irrecv.resume(); // Receive the next value
 
    }
}
}
