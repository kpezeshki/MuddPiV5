/*
 * sam_backend.c
 *
 * Created: 12/7/2018 5:18:33 PM
 * Author : Kaveh Pezeshki and Chris Ferrarin
 * 
 * MCU backend for Lab 6. Generates webpages as requested by the ESP8266, and interfaces with the onboard PIO and ADC peripherals to allow user control of an LED and to display the current time.
 * 
 */ 


#include "easySamIO.h"
#include <string.h>

#define LED_PIN 16

//Defining the web page in two chunks: everything before the current time, and everything after the current time
//Please see the e155 website for a human-readable version of the file "webpage.html"
const char* webpageStart = "<!DOCTYPE html><html>\n    <head>\n        <title>E155 Web Server Demo Webpage</title>\n        <meta http-equiv=\"refresh\" content=\"5\">\n    </head>\n    <body>\n        <h1>E155 Web Server Demo Webpage</h1>\n        <p>Current Microcontroller Time:</p>\n        ";
const char* webpageEnd   = "\n        <p>LED Control:</p>\n        <form action=\"ledon\">\n            <input type=\"submit\" value=\"Turn the LED on!\" />\n        </form>\n        <form action=\"ledoff\">\n                <input type=\"submit\" value=\"Turn the LED off!\" />\n        </form>\n    </body>\n</html>";
const int webpageStartChars = 255;
const int webpageEndChars = 268;

int main(void)
{
    //Initialize peripheral clocks
	samInit();
	//Initialize GPIO pin  for LED control
	pinMode(LED_PIN, OUTPUT);
	//Initialize UART with no parity, 9600 baud
	//The peripheral clock is 4MHz, and we provide a clock divider factor CD such that baud rate = MCK/(16*CD)
	//Therefore we need a clock divide coefficient of 26, which provides a baud rate of 9615 baud. This 0.1% error is accounted for by the receiving UART
	uartInit(4, 26);
	//Initialize RTC
	//TODO: this
		
    /* Replace with your application code */
    while (1) 
    {
		//wait for the ESP8266 to send a request. Requests take the form 'REQ:<tag>/REQ', with TAG being <= 10 characters. Therefore the request[] array must be able to contain 18 characters
		char request[18] = "                  "; //initializing to a known value
		int  charIndex = 0;
		while (requestInString(request) == -1 && charIndex < 18) {
			//wait for a complete request to be transmitted before processing
			request[charIndex] = uartRx();
			//this has the potential for an off-by-one error. This is mitigated by clearing request if "/REQ" but not "REQ:" is in the string
			if (inString(request, "/REQ") == 1 && inString(request, "REQ:") == -1) {
				for (int i = 0; i < 18; i++) {
					request[i] = " ";
				}
				charIndex = 0;
			}
			//incrementing charIndex
			charIndex++;
		}
		
		//the request has been received. now process to determine whether to turn the LED on or off
		if (inString(request, "ledon")) {
			digitalWrite(LED_PIN, HIGH);
		}
		else if (inString(request, "ledoff")) {
			digitalWrite(LED_PIN, LOW);
		}
		
		//next, read the RTC and create a string representation of the current time.
		char currtime[] = "12:34:56";
		int  currtimeLen = 8;
		
		//finally, transmit the webpage over UART
		//transmitting the first section of the webpage
		for (int charCount = 0; charCount < webpageStartChars; charCount++) {
			uartTx(webpageStart[charCount]);
		}
		//transmitting the current time
		for (int charCount = 0; charCount < currtimeLen; charCount++) {
			uartTx(currtime[charCount]);
		}
		//transmitting the last section of the webpage
		for (int charCount = 0; charCount < webpageEndChars; charCount++) {
			uartTx(webpageEnd[charCount]);
		}	
    }
}

//determines whether a given character sequence is in a char array request, returning 1 if present, -1 if not present
int inString(char request[], char des[]) {
	if (strstr(request, des) != NULL) {return 1;}
	return -1;
}

//determines if tags "REQ:" and "/REQ" are in the input string
int requestInString(char request[]) {
	int tag1InString = inString(request, "REQ:");
	int tag2InString = inString(request, "/REQ");
	if(tag1InString == 1 && tag2InString == 1) {
		return 1;
	}
	return -1;
}
