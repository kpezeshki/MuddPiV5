
#define LED_PIN 13


String webpageStart = "<!DOCTYPE html><html>\n    <head>\n        <title>E155 Web Server Demo Webpage</title>\n        <meta http-equiv=\"refresh\" content=\"5\">\n    </head>\n    <body>\n        <h1>E155 Web Server Demo Webpage</h1>\n        <p>Current Microcontroller Time:</p>\n        ";
String webpageEnd   = "\n        <p>LED Control:</p>\n        <form action=\"ledon\">\n            <input type=\"submit\" value=\"Turn the LED on!\" />\n        </form>\n        <form action=\"ledoff\">\n                <input type=\"submit\" value=\"Turn the LED off!\" />\n        </form>\n    </body>\n</html>";


void setup(void)
{
  //Initialize GPIO pin  for LED control
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial.println("Running");

}

void loop() {
  if (Serial1.available()) {
    Serial.println("Webpage Recieved");
    Serial1.print(webpageStart);
    Serial1.println(millis());
    Serial1.print(webpageEnd);
    delay(10);
    while (Serial1.available()) Serial1.read();
  }
}
