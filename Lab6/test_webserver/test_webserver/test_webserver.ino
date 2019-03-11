/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>


// Replace with your network credentials
const char* ssid     = "ESPTest";
const char* password = NULL;

//defining start and end HTML tags
const String htmlStart = "<!DOCTYPE html><html>";
const String htmlEnd = "</html>";

String     parsedRequest;        //Stores a simplified version of the HTTP request to transmit to the MCU
bool       fetchWebpage = false; //after the client has connected and disconnected, we fetch a new webpage from the MCU

String webpage = "<!--Kaveh Pezeshki and Christopher Ferrarin-->\n<!--Demo webpage for E155 lab 6-->\n\n<!DOCTYPE html><html>\n    <head>\n        <title>E155 Web Server Demo Webpage</title>\n        <meta http-equiv=\"refresh\" content=\"5\">\n    </head>\n    <body>\n        <h1>E155 Web Server Demo Webpage</h1>\n        <p>Current Microcontroller Time:</p>\n        00:00:00\n        <p>LED Control:</p>\n        <form action=\"on\">\n            <input type=\"submit\" value=\"Turn the LED on!\" />\n        </form>\n        <form action=\"off\">\n                <input type=\"submit\" value=\"Turn the LED off!\" />\n        </form>\n    </body>\n</html>";
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

//Defining the softwareSerial interface
SoftwareSerial mcuSerial(14, 15);

void setup() {
  Serial.begin(115200);
  mcuSerial.begin(9600);
  Serial.println("Set up serial connections");

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //receiveWebPage("<>");
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  server.begin();
}

void loop(){
  WiFiClient webClient = server.available();   // Listen for incoming clients

  if (webClient) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (webClient.connected()) {            // loop while the client's connected
      if (webClient.available()) {             // if there's bytes to read from the client,
        char c = webClient.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            Serial.println("Transmitting webpage");
            webClient.println("HTTP/1.1 200 OK");
            webClient.println("Content-type:text/html");
            webClient.println("Connection: close");
            webClient.println();
            webClient.println(webpage);
            // Break out of the while loop
            fetchWebpage = true;
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
    parsedRequest = parseRequest(header);
    Serial.println(parsedRequest);
    header = "";
    // Close the connection
    webClient.stop();
    Serial.println("webClient disconnected.");
    Serial.println("");
  }
    if (fetchWebpage) {
    fetchWebpage = false;
    //webpage = receiveWebPage(parsedRequest);
  }
}

//Parses an input http request as specified in "Abbreviated URL Explanation"
String parseRequest(String request) {
  Serial.print("////START Received Request: ");
  Serial.println(request);
  Serial.println("////END Received Request: ");

  if (request.indexOf("favicon.ico") != -1) return "<>";

  int getLocation = request.indexOf("GET /");
  int httpLocation = request.indexOf(" HTTP");

  String parsedRequest = "<" + request.substring(getLocation + 5, httpLocation) + ">";

  Serial.print("Reduced URL: '");
  Serial.print(parsedRequest);
  Serial.println("'");
  return parsedRequest;
}

//Sends parsedRequest over UART to the MCU and waits for a complete webpage to be returned
String receiveWebPage(String parsedRequest) {
  Serial.println("////START Received Web Page");
  webpage = ""; //clear webpage in preparation for new webpage to be transmitted
  bool webpageReceived = false;
  //transmitting the parsed request from the client
  mcuSerial.print(parsedRequest);
  //wait until the entire webpage has been received

  while (!webpageReceived) {
    ESP.wdtFeed(); //resetting watchdog timer
    //checking for new serial data, adding to website
    if (mcuSerial.available()) {
      String newData = mcuSerial.readString();
      webpage += newData;
      bool startReceived = (webpage.indexOf(htmlStart) != -1);
      bool endReceived = (webpage.indexOf(htmlEnd) != -1);
      webpageReceived = startReceived && endReceived;
    }

  }
  Serial.println("Received webpage");
  Serial.println(webpage);
  Serial.println("////END Received Web Page");
  return webpage;
}
