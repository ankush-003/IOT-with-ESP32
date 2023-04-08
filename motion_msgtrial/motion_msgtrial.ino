#include "twilio.hpp"

//define sound speed in cm/uS
#define CM_TO_INCH 0.393701
#define SOUND_SPEED 0.034
const int trigPin = 5;
const int echoPin = 12;


long duration;
float distanceCm;
float distanceInch;

// Wifi Setup
static const char *ssid = "Gipsydngr";
static const char *password = "chutiyappa";

// Values from Twilio 
static const char *account_sid = "ACe728b1a221eb6b1a2809f7ad50bc431c";
static const char *auth_token = "922cad57c0b27f66aa179e20521f002d";

static const char *from_number = "+15076657983";

static const char *to_number = "+9186182105439";
static const char *message = "Sent from my ESP32-Hello MF";
static char *warning = "Motion Detected!";


Twilio *twilio;
void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network ;");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

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
  // detecting motion:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  delay(1000);
  if(distanceCm < 10) {
    bool success = twilio->send_message(to_number, from_number, warning, response);
    if (success) {
      Serial.println("Warning sent message successfully!");
      digitalWrite(2, HIGH);
    } else {
      Serial.println(response);
    }
  }
}
