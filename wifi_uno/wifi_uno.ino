#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "Gipsydngr";
const char* password = "chutiyappa";

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
  
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for data from client to become available
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the HTTP request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // If the request is for the root path
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
  }
  else if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
  }

  // Send a response to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html>");
  client.println("<head><title>ESP8266 LED Control</title></head>");
  client.println("<body>");
  client.println("<h1>ESP8266 LED Control</h1>");
  client.println("<p>Click the buttons below to turn the LED on or off:</p>");
  client.println("<form>");
  client.println("<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/LED=ON'\">");
  client.println("<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/LED=OFF'\">");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
}