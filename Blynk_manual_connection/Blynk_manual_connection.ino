// /*********************
//   Blynk is a platform with iOS and Android apps to control
//   ESP32, Arduino, Raspberry Pi and the likes over the Internet.
//   You can easily build mobile and web interfaces for any
//   projects by simply dragging and dropping widgets.

//     Downloads, docs, tutorials: https://www.blynk.io
//     Sketch generator:           https://examples.blynk.cc
//     Blynk community:            https://community.blynk.cc
//     Follow us:                  https://www.fb.com/blynkapp
//                                 https://twitter.com/blynk_app

//   Blynk library is licensed under MIT license
//  *********************
//   Blynk.Edgent implements:
//   - Blynk.Inject - Dynamic WiFi credentials provisioning
//   - Blynk.Air    - Over The Air firmware updates
//   - Device state indication using a physical LED
//   - Credentials reset using a physical Button
//  *********************/

// /* Fill in information from your Blynk Template here */
// /* Read more: https://bit.ly/BlynkInject */
// #define BLYNK_TEMPLATE_ID "TMPL6zFM469wx"
// // #define BLYNK_TEMPLATE_ID "TMPLxOgnvgE6"
// #define BLYNK_TEMPLATE_NAME "ledblink"

// #define BLYNK_FIRMWARE_VERSION        "0.1.0"

// #define BLYNK_PRINT Serial
// //#define BLYNK_DEBUG

// #define APP_DEBUG

// // Uncomment your board, or configure a custom board in Settings.h
// //#define USE_ESP32_DEV_MODULE
// //#define USE_ESP32C3_DEV_MODULE
// //#define USE_ESP32S2_DEV_KIT
// //#define USE_WROVER_BOARD
// //#define USE_TTGO_T7
// //#define USE_TTGO_T_OI

// #include "BlynkEdgent.h"

// BLYNK_WRITE(V0)
// {
//   int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
//   digitalWrite(2,pinValue);
// // process received value
// }

// BLYNK_WRITE(V1)
// {
//   int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
//   digitalWrite(2,pinValue);
// // process received value
// }


// void setup()
// {
//   pinMode(2, OUTPUT) ; 
//   Serial.begin(115200);
//   delay(100);
//   BlynkEdgent.begin();
// }

// void loop() {
//   BlynkEdgent.run();
// }

/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6ZvE8cGNG"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "HK56DiFEdlncbfLq_C5wMaQjMK6sf4qq"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Ankush_4G";
char pass[] = "ankushin2003";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(2,pinValue);
// process received value
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

