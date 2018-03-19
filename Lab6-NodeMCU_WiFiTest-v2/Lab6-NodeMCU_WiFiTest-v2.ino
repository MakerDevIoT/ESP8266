#include <ESP8266WiFi.h>                  // Include ESP8266 library
#define ssid "Jirawin"          // SSID is set
#define password "Win460220"   // Password is set
#define LEDpin D0
void setup()
{
  Serial.begin(115200);                   // Enable UART
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");         // Print title message to the serial monitor
  Serial.println(ssid);                   // Print SSID name
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, 0);                // WiFi detected indicator - active low
  WiFi.begin(ssid, password);             // Send password
  while (WiFi.status() != WL_CONNECTED)   // Check WiFi status
  {
    delay(1500);
    Serial.print(".");                    // Print dot for showing the progress status
  }
  Serial.println("");
  Serial.println("WiFi connected");       // Print the connected message
  Serial.println("IP address: ");         // Print IP address
  Serial.println(WiFi.localIP());
}
void loop()
{
  digitalWrite(LEDpin, 0);                // WiFi connected indicator - active low
  while (WiFi.status() != WL_CONNECTED)   // Check WiFi status
  {
    digitalWrite(LEDpin, 0);              // LED at D0 blink when disconnect WiFi
    delay(400);
    Serial.println("connection WiFi failed");   // Print error message to Serial Monitor
    digitalWrite(LEDpin, 1);
    delay(100);
  }
}

