#include <ESP8266WiFi.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE

#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>
#include "LedMatrix.h"

const byte chips = 4;//how many display modules
unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 25;  // mS
int  messageOffset;

MAX7219_Dot_Matrix display (chips, 2);  // Chips / LOAD 

char message [90] = "";
String me="";

const char* ssid = "RT-N16"; // put your router name
const char* password = "mailmail";// put your password 
 
const char* host = "api.thingspeak.com";

int value = 0;

int find_text(String needle, String haystack,int from) {
  int foundpos = -1;
  if (haystack.length()<needle.length())
    return foundpos;
  for (int i = from; (i < haystack.length() - needle.length()); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
      return foundpos;
    }
  }
  return foundpos;
}

void updateDisplay ()
  {
  display.sendSmooth (message, messageOffset);
  
  // next time show one pixel onwards
  if (messageOffset++ >= (int) (strlen (message) * 8))
    messageOffset = - chips * 8;
  }  // end of updateDisplay

 
void setup() {


  
    
  display.begin ();



  
  Serial.begin(115200);
  delay(100);
 
 
 
 // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 





 
void loop() {
 
 
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }
  
  // We now create a URI for the request
  String url = "/apps/thinghttp/send_request?api_key=ZMWY350CCZFKKXAU";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
 // delay(2000);
  for (int i=0;i<2000;i++)
  {
  delay(1);


  // update display if time is up
  if (millis () - lastMoved >= MOVE_INTERVAL)
    {
    updateDisplay ();
    lastMoved = millis ();
    }


  
  }
  me=" GOOG price:";  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
   String line = client.readStringUntil('\r');
   

 

int start_loc= find_text("price.0",line,0);
if (start_loc>0) start_loc+=6;
int end_loc=find_text("</span>",line,0);


if (start_loc>0 && end_loc>0)
{
  Serial.println("price:  ");

for (int i=start_loc+3;i<end_loc;i++)
{
Serial.print(line[i]);
me+=line[i];

}
Serial.println("");
me+=" change: ";
int start_loc2= find_text("price.1",line,end_loc+1)+6;

 //Serial.println(line);
int end_loc2=find_text("</span",line,end_loc+1);
if (start_loc2>0 && end_loc2>0)
{
  
  Serial.println("views:");
for (int i=start_loc2+3;i<end_loc2;i++)
{
 
Serial.print(line[i]);
me+=line[i];
}
}


}
    
 //   Serial.println(line);
  }
  
  Serial.println();
  Serial.println("closing connection");

for (int i=0;i<90;i++)
message[i]=me[i];



for(int i=0;i<80000;i++)
{
  delay(1);
   // update display if time is up
  if (millis () - lastMoved >= MOVE_INTERVAL)
    {
    updateDisplay ();
    lastMoved = millis ();
    }

  // do other stuff here    
}
 
  
 
  
 
  
 
  
 
 
}
