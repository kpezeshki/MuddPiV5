/*
 * Kaveh Pezeshki and Christopher Ferrarin
 * E155 Lab 6
 * 
 * Displays a voltage string sent over UART, printing the button state whenever it is updated
 * Much of the basic ESP8266 code adapted from: https://randomnerdtutorials.com/esp8266-web-server/
 * RX = D2
 * TX = D3
 */

 //Loading the ESP8266 library
 #include <ESP8266WiFi.h>
 #include <SPISlave.h>
 #include <SoftwareSerial.h> 

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
                             "<body><h1>E155 Lab6: ESP8266 SPI Slave</h1>",
                             //button will be displayed here
                             "</body></html>",
                             ""
                          };
                             
                             
                             

 //Defining network information
 const char* networkName = "ESPTest";
 const char* password = NULL; 

 //Defining the web server and HTTP request variables
 WiFiServer server(80);
 String request; //storing HTTP request
 String currentLine; //storing incoming data from the client 
 int    buttonState = 0;   //the data to return in an SPI transaction, current state of webpage button
 String voltage; //the voltage data sent from the SPI master

 //Defining the softwareSerial implementation
 SoftwareSerial NodeMCU(2, 3);

 void setup() {
  Serial.begin(9600); //keeping a serial connection open for debugging
  Serial.setDebugOutput(true);
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
  //Starting a software serial connection
  NodeMCU.begin(9600);
   
  /*
  SPISlave.onData([](uint8_t * data, size_t len) {
    String message = String((char *)data);
    (void) len;
    Serial.print("Received data from master: ");
    Serial.println(message);
    voltage = message;
    SPISlave.setData(buttonState);
  });

  // The master has read out outgoing data buffer
  // that buffer can be set with SPISlave.setData
  SPISlave.onDataSent([]() {
    Serial.println("Answer Sent");
  });

  // status has been received from the master.
  // The status register is a special register that bot the slave and the master can write to and read from.
  // Can be used to exchange small data or status information
  SPISlave.onStatus([](uint32_t data) {
    Serial.printf("Status: %u\n", data);
    SPISlave.setStatus(millis()); //set next status
  });

  // The master has read the status register
  SPISlave.onStatusSent([]() {
    Serial.println("Status Sent");
  });

  // Setup SPI Slave registers and pins
  SPISlave.begin();
  
  // Sets the data registers. Limited to 32 bytes at a time.
  // SPISlave.setData(uint8_t * data, size_t len); is also available with the same limitation
  SPISlave.setData(buttonState); */
  
}



void loop() {
  //updating buttonState
  while(NodeMCU.available()) {
    char character = NodeMCU.read();
    Serial.print("received from UART: ");
    Serial.println(character);
    if (character == '/') {voltage = "";}
    else voltage.concat(character);
  }
  
  //Listening for new connections
  WiFiClient webClient = server.available();
  //Passing the webpage if a new client connects
  if (webClient) {
    Serial.println("Client connected");
    Serial.println("Button State");
    Serial.print(buttonState);
    NodeMCU.print(buttonState);
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
              NodeMCU.print(1);
            }
            if (request.indexOf("GET /1/off") >= 0) {
              buttonState = 0;
              NodeMCU.print(0);
            }
            //displaying the webpage
            Serial.println("transmitting webpage...");
            for (int i = 0; i < 8; i++) { //lines before button press
              webClient.println(webpage[i]);
              Serial.println(webpage[i]);
            }
            //displaying SPI input data
            webClient.println("<p>Voltage: " + voltage + "</p>");
            Serial.println("<p>Voltage: " + voltage + "</p>");
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
