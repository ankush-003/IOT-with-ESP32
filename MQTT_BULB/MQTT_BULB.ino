#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define led 2
// Deklarasi Variable dan Konstanta
String wifiSSID = "Gipsydngr";
String wifiPassword = "chutiyappa";
String mqttBroker = "test.mosquitto.org";
WiFiClient client;
PubSubClient mqtt(client);

// Deklarasi Fungsi
void connectWifi();
void connect_mqtt();
String randomTemp();
void mqttReceivedMessage(char *topic, byte *msg, unsigned int msgLength);
void setup()
{
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    connectWifi();
    mqtt.setServer(mqttBroker.c_str(), 1883);
    mqtt.setCallback(mqttReceivedMessage);
}

void loop()
{
    if (!mqtt.connected())
    {
        connect_mqtt();
        Serial.println("MQTT Connected");
        mqtt.publish("esp32_Ankush", "ESP 32 Online!");
    }
    mqtt.loop();
    // mqtt.publish("esp32/temphum", randomTemp().c_str());
    // delay(1000);
}

void mqttReceivedMessage(char *topic, byte *msg, unsigned int msgLength)
{
    if (String(topic) == "esp32_Ankush")
    {
        Serial.println(topic);
        String perintah = "";
        for (int i = 0; i < msgLength; i++)
        {
            Serial.print(char(msg[i]));
            perintah += String(char(msg[i]));
        }
        Serial.println("");
        Serial.println(perintah);
        if (perintah == "ON")
        {
            digitalWrite(led, 1);
        }
        else if (perintah == "OFF")
        {
            digitalWrite(led, 0);
        }
    }
}

String randomTemp()
{

    int randTemp = random(20, 40);
    Serial.println(randTemp);
    return String(randTemp);
}

void connect_mqtt()
{
    while (!mqtt.connected())
    {
        Serial.println("Connecting MQTT...");
        if (mqtt.connect("esp32_Ankush"))
        {
            mqtt.subscribe("esp32_Ankush");
        }
    }
}

void connectWifi()
{
    Serial.println("Connecting To Wifi");
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Wifi Connected");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.dnsIP());
}