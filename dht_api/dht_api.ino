#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>  // Including library for dht
  
String apiKey = "XU4O9C9FDGUKD5D7";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Gipsydngr";     // replace with your wifi ssid and wpa2 key
const char *pass =  "chutiyappa";
const char* server = "api.thingspeak.com";
int channelID = 2082615;
unsigned long myChannelNumber = 2082615;
 
#define DHTPIN 2          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
      ThingSpeak.begin(client);
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                            //  String postStr = apiKey;
                            //  postStr +="&field1=";x
                            //  postStr += String(t);
                            //  postStr +="&field2=";
                            //  postStr += String(h);
                            //  postStr += "\r\n\r\n";
 
                            //  client.print("POST /update HTTP/1.1\n");
                            //  client.print("Host: api.thingspeak.com\n");
                            //  client.print("Connection: close\n");
                            //  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                            //  client.print("Content-Type: application/x-www-form-urlencoded\n");
                            //  client.print("Content-Length: ");
                            //  client.print(postStr.length());
                            //  client.print("\n\n");
                            //  client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                            //  Serial.println("%. Send to Thingspeak.");
                            // int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureC, myWriteAPIKey);
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}