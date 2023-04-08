#include "twilio.hpp"

// Set these - but DON'T push them to GitHub!
static const char *ssid = "Gipsydngr";
static const char *password = "chutiyappa";

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "ACe728b1a221eb6b1a2809f7ad50bc431c";
static const char *auth_token = "922cad57c0b27f66aa179e20521f002d";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+15076657983";

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "+9186182105439";
static const char *message = "Sent from my ESP32-Hello MF";
static const char *warning = "Motion Detected!";


Twilio *twilio;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network ;");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected!");

  twilio = new Twilio(account_sid, auth_token);

  delay(1000);
  String response;
  bool success = twilio->send_message(to_number, from_number, message, response);
  if (success) {
    Serial.println("Sent message successfully!");
    digitalWrite(2, HIGH);
  } else {
    Serial.println(response);
  }
}

void loop() {

}