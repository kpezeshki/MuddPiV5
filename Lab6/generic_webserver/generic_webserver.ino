/*
   Kaveh Pezeshki and Christopher Ferrarin
   E155 Lab 6 Generic Webserver

   Hosts a webserver displaying webpages sent over UART, sending back redirect URLs to provide a measure of user interaction.

   In more detail:

   1) The webserver starts a 9600 baud serial connection over the hardware UART (for debug)
   2) The webserver starts a 9600 baud software serial connection over pins 14 and 15 (RX, TX)
   3) The webserver connects to a given network, and prints status information over the debug UART. By default, this is CINE.
   4) The webserver waits for a request from the client, after which it sends a string to the MCU: "REQ:" + <abbr. url> + "/REQ"
   5) The webserver waits for the MCU to send over an HTML webpage, defined as "<!DOCTYPE html><html> ... </html>"
   6) The webserver displays this webpage to any connected clients

   steps 4-6 are repeated while the program runs

   Abbreviated URL explanation:
   The webserver automatically parses a client request to simplify code on the MCU. If the server has example IP address '192.168.1.1', a client request may be the URL:
   'http://192.168.1.1/webpage'
   The server will return everything after the IP address and slash. For example:
   'http://192.168.1.1/webpage' => 'R:webpage/R'

   We expect these abbreviated URLs to be under 10 characters
*/

//Importing required libraries
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

//defining start and end HTML tags
const String htmlStart = "<!DOCTYPE html><html>";
const String htmlEnd = "</html>";

//Defining network information
const char* networkName = "CINE"; //set this to the selected network SSID
const char* password    = NULL;   //set this to a non-null value if selected network requires authentication
String      ip;                   //stores the current IP. Set in the setup function

//Defining the web server and HTTP request variables
WiFiServer server(80);           //The server is accessible over port 80
String     request;              //Stores the client HTTP request
String     parsedRequest;        //Stores a simplified version of the HTTP request to transmit to the MCU
String     currentLine;          //Stores a semi-parsed version of the HTTP request
String     webpage = "abcdefg";  //The current webpage, updated by the MCU
bool       fetchWebpage = false; //after the client has connected and disconnected, we fetch a new webpage from the MCU

//Defining the softwareSerial interface
SoftwareSerial mcuSerial(14, 15);

//Setup code. Runs once on program execution before loop code
void setup() {
  //starting the debug and MCU serial connections
  Serial.begin(9600);
  mcuSerial.begin(9600);
  Serial.println("Set up serial connections");

  //connecting to WiFi network
  Serial.print("Connecting to network ");
  Serial.println(networkName);
  Serial.print("With password ");
  Serial.println(password);
  WiFi.begin(networkName, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Attempting connection...");
  }
  //connected to the network. Printing status information
  Serial.print("Connected to WiFi network with IP: ");
  Serial.println(WiFi.localIP());
  ip = ipToString(WiFi.localIP());

  //starting server
  Serial.println("Starting server");
  server.begin();
}

//Main program. Runs repeatedly after setup code
void loop() {
  //Wait for a new connection
  WiFiClient webClient = server.available();
  //If a client has connected, we wait for a request
  if (webClient) {
    fetchWebpage = true;
    Serial.println("\nClient Connected");
    while (webClient.connected()) {
      //Reading available bytes from the client if available
      if (webClient.available()) {
        char byteIn = webClient.read();
        request += byteIn;

        //if the line is only a line feed, we have reached the end of the client request and will therefore send a response
        //This requires sending a request for a new webpage to the MCU
        if (byteIn == '\n') {
          if (currentLine.length() == 0) {
            //transmitting the response
            Serial.println("Transmitting webpage");
            webClient.println(webpage);
            //updating the webpage
            parsedRequest = parseRequest(request);
            webpage = receiveWebPage(parsedRequest);
            break; //disconnect from the client by breaking from while loop
          }
          else {
            currentLine = "";
          }
        }
        else if (byteIn != '\r') {
          currentLine += byteIn;
        }
      }
    }
    //ending the transaction
    request = "";
    webClient.stop();
    Serial.println("Client disconnected");
  }
  //we update the webpage after the client has disconnected to prevent any timeout errors
  if (fetchWebpage) {
    fetchWebpage = false;
    parsedRequest = parseRequest(request);
    webpage = receiveWebPage(parsedRequest);
  }
}

//Converts an IP address to a String
String ipToString(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

//Parses an input http request as specified in "Abbreviated URL Explanation"
String parseRequest(String request) {
  Serial.print("////START Received Request: ");
  Serial.println(request);
  Serial.print("////END Received Request: ");

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
