/*
 * Interface InfraRed Sensor Using NodeMCU
 * By TheCircuit
 * Red :     5V
 * Brown: Sensor output
 * Black : Ground
*/

int ledPin = 14; // choose pin for the LED
int inputPin = 5; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status 
void setup() 
{ 
   pinMode(ledPin, OUTPUT); // declare LED as output 
   pinMode(inputPin, INPUT); // declare Infrared sensor as input
} 
void loop()
{ 
   val = digitalRead(inputPin); // read input value 
   if (val == HIGH)
   { // check if the input is HIGH
      digitalWrite(ledPin, LOW); // turn LED OFF   
   } 
   else 
   { 
      digitalWrite(ledPin, HIGH); // turn LED ON 
   } 
}
