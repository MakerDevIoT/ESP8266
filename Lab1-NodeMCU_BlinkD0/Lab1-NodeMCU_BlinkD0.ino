int LEDpin6 = D6;
int LEDpin7 = D7;
void setup() 
{
  pinMode(LEDpin6, OUTPUT);
  pinMode(LEDpin7, OUTPUT);
}
void loop() 

{
  digitalWrite(LEDpin6,HIGH); // ไฟติด
  digitalWrite(LEDpin7,HIGH); // ไฟติด
  delay(200);
  digitalWrite(LEDpin6,LOW); // ไฟดับ
  digitalWrite(LEDpin7,LOW); // ไฟดับ
  delay(200);
}
