#include <WiFi.h>
// Replace with your network credentials
const char* ssid = "Ankush_4G";
const char* password = "ankushin2003";
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
// Auxiliary variables to store the current output state
String outputRedState = "off";
String outputGreenState = "off";
String outputBlueState = "off";
// Assign output variables to GPIO pins
const int outputBlue = 2;
const int outputRed = 14;
const int outputGreen = 13;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(outputBlue, OUTPUT);
  pinMode(outputRed, OUTPUT);
  pinMode(outputGreen, OUTPUT);

  // Set outputs to LOW
  digitalWrite(outputBlue, LOW);
  digitalWrite(outputRed, LOW);
  digitalWrite(outputGreen, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the GPIOs on and off
            if (header.indexOf("GET /Blue/on") >= 0) {
              Serial.println("GPIO 2 on");
              outputBlueState = "on";
              digitalWrite(outputBlue, HIGH);
            } else if (header.indexOf("GET /Blue/off") >= 0) {
              Serial.println("GPIO 2 off");
              outputBlueState = "off";
              digitalWrite(outputBlue, LOW);
            } else if (header.indexOf("GET /Red/on") >= 0) {
              Serial.println("GPIO 14 on");
              outputRedState = "on";
              digitalWrite(outputRed, HIGH);
            } else if (header.indexOf("GET /Red/off") >= 0) {
              Serial.println("GPIO 14 off");
              outputRedState = "off";
              digitalWrite(outputRed, LOW);
            } else if(header.indexOf("GET /Green/on") >= 0) {
              Serial.println("GPIO 13 on");
              outputRedState = "on";
              digitalWrite(outputGreen, HIGH);
            } else if(header.indexOf("GET /Green/off") >= 0) {
              Serial.println("GPIO 13 off");
              outputRedState = "off";
              digitalWrite(outputGreen, LOW);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ\" crossorigin=\"anonymous\">");
            client.println("<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ENjdO4Dr2bkBIFxQpeoTz1HIcje39Wm4jDKdf19U8gI4ddQ3GYNS7NTKfAdVQSZe\" crossorigin=\"anonymous\"> </script>");
            client.println("<title>Home Dashboard</title>");

            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            // Web Page Heading

            client.println("<body>");
            client.println("<div class=\"container-fluid-nav fw-medium fs-2 text-center bg-black text-white py-3 h-10\">");
            client.println("<p class=\"text-center\">Welcome To Dashboard</p></div>");
            // Display current state, and ON/OFF buttons for GPIO 12  
            // client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // // If the output12State is off, it displays the ON button      
            // if (output12State=="off") {
            //   client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            // } else {
            //   client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            // }
            
            client.println("<div class=\"container-fluid d-flex justify-content-center mt-3\">");
            client.println("<div class=\"btn-group-vertical row pt-3 mt-5\" role=\"group\" aria-label=\"Vertical button group\">");
            if(outputRedState == "off") {
            client.println("<a href=\"/Red/on\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-danger\">OFF</button></a>");
            } else {
            client.println("<a href=\"/Red/off\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-danger\">ON</button></a>");
            }
            // if(outputRedState == "off") {
            // client.println("<button type=\"button\" href=\"/Red\on\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-danger\">OFF</button>");
            // } else {
            // client.println("<button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-danger\">ON</button>");
            // }

            if(outputBlueState == "off") {
            client.println("<a href=\"/Blue/on\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-primary\">OFF</button></a>");
            } else {
            client.println("<a href=\"/Blue/off\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-primary\">ON</button></a>");
            }

            if(outputGreenState == "off") {
            client.println("<a href=\"/Green/on\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-success\">OFF</button></a>");
            } else {
            client.println("<a href=\"/Green/off\"><button type=\"button\" class=\"btn col-6 py-3 px-3 my-3 mx-3 btn-lg rounded btn-outline-success\">ON</button></a>");
            }

            client.println("</div></div>");
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
