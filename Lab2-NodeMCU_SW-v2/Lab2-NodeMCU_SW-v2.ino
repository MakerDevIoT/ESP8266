#define sw1 D5                    // Define D5 as switch pin
#define ledPin1 D6                // Define D6 as LED pin
#define ledPin2 D7   
int st_sw1 = 0;
uint8_t state;
void setup()
{
  pinMode(ledPin1, OUTPUT);       // Set pin as output
  pinMode(ledPin2, OUTPUT); 
  pinMode(sw1, INPUT);            // set pin as input
  Serial.begin(115200);
}
void loop()
{
  st_sw1 = digitalRead(sw1);      // Read input
  Serial.println(st_sw1); 
  if(st_sw1==1){
     state = LOW;
  }else{
    state = HIGH;
  }
  digitalWrite(ledPin1, state); // Invert output
  digitalWrite(ledPin2, state);
}

