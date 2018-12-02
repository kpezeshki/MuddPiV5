/*
 * Kaveh Pezeshki and Christopher Ferrarin
 * E155 Lab 6
 * 
 * Displays a 5-char string sent over SPI on a webpage, serving as an SPI slave
 * Returns a 1 or 0 in the all SPI transactions, representing the state of a toggle on the webpage
 * Much of the basic ESP8266 code adapted from: https://randomnerdtutorials.com/esp8266-web-server/
 */

 //Loading the ESP8266 library
 #include <ESP8266WiFi.h>

 //defining response and webpage for client
 const char* response[] = { 
                             "HTTP/1.1 200 OK",
                             "Content-type:text/html",
                             "Connection: close",
                             ""
                          };
                           
 const char* webpage[]  = { 
                             "<!DOCTYPE html><html>",
                             "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">",
                             "<link rel=\"icon\" href=\"data:,\">",
                             "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}",
                             ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;",
                             "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}",
                             ".button2 {background-color: #77878A;}</style></head>",
                             "<body><h1>ESP8266 Web Server</h1>",
                             //button will be displayed here
                             "</body></html>",
                             ""
                          };
                             
                             
                             

 //Defining network information
 const char* networkName = "CINE";
 const char* password = NULL; 

 //Defining the web server and HTTP request variables
 WiFiServer server(80);
 String request; //storing HTTP request
 String currentLine; //storing incoming data from the client 
 int    buttonState = 0;   //the data to return in an SPI transaction

 void setup() {
  Serial.begin(9600); //keeping a serial connection open for debugging
  Serial.println("Connecting to Network");
  WiFi.begin(networkName, password);
  //waiting until connection to network complete
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Attempting connection...");
  }
  //At this point we are connected to the network. Printing status information:
  Serial.print("Connected to WiFi network with IP: ");
  Serial.println(WiFi.localIP());
  //Starting server
  Serial.println("Starting server");
  server.begin();

}

void loop() {
  //Listening for new connections
  WiFiClient webClient = server.available();
  //Passing the webpage if a new client connects
  if (webClient) {
    Serial.println("Client connected");
    currentLine = "";
    while (webClient.connected()) {
      if (webClient.available()) { //if there are bytes to read from the client
        char byteIn = webClient.read();
        Serial.write(byteIn);
        request += byteIn;
        //if the received line is empty, and a newline characted is received, this is the end of the client HTTP request, so send a response
        if (byteIn == '\n') {
          if (currentLine.length() == 0) {
            //transmitting response
            Serial.println("transmitting response...");
            for (int i = 0; i < 4; i++) {
              webClient.println(response[i]);
              Serial.println(response[i]);
            }
            if (request.indexOf("GET /1/on") >= 0) {
              buttonState = 1;
            }
            if (request.indexOf("GET /1/off") >= 0) {
              buttonState = 0;
            }
            //displaying the webpage
            Serial.println("transmitting webpage...");
            for (int i = 0; i < 8; i++) { //lines before button press
              webClient.println(webpage[i]);
              Serial.println(webpage[i]);
            }
            //displaying the button
            if (buttonState==0) {
              webClient.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
              Serial.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              webClient.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
              Serial.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //displaying the remainder of the webpage
            for (int i = 8; i < 10; i++) {
              webClient.println(webpage[i]);
              Serial.println(webpage[i]);
            }
            //breaking out of the while loop
            break; 
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
}
