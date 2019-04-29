/*
 * sam_backend.c
 *
 * Created: 12/7/2018 5:18:33 PM
 * Author : Kaveh Pezeshki and Chris Ferrarin
 * 
 * MCU backend for Lab 6. Generates webpages as requested by the ESP8266, and interfaces with the onboard PIO and ADC peripherals to allow user control of an LED and to display the current time.
 * 
 */ 


#include "SAM4S4BDeviceDriver/SAM4S4B.h"
#include <string.h>

#define LED_PIN 18
#define BUFF_LEN 32

//Defining the web page in two chunks: everything before the current time, and everything after the current time
//Please see the e155 website for a human-readable version of the file "webpage.html"
const char* webpageStart = "<!DOCTYPE html><html><head><title>E155 Web Server Demo Webpage</title><meta http-equiv=\"refresh\" content=\"5\"></head><body><h1>E155 Web Server Demo Webpage</h1>";
const char* microcontrollerTimeStr = "<p>Current Microcontroller Time:</p>";
const char* ledStr = "<p>LED Control:</p><form action=\"ledon\"><input type=\"submit\" value=\"Turn the LED on!\" /></form> <form action=\"ledoff\"><input type=\"submit\" value=\"Turn the LED off!\" /></form>";
const char* temperatureStr = "<p>Current Temperature:</p>";
const char* humidityStr = "<p>Current Humidity:</p>";
const char* webpageEnd   = "</body></html>";



int main(void)
{
    //Initialize peripheral clocks
	samInit();
	//Initialize GPIO pin  for LED control
	pioPinMode(LED_PIN, PIO_OUTPUT);
	pioDigitalWrite(LED_PIN, PIO_HIGH);
	//Initialize UART with no parity, 9600 baud
	//The peripheral clock is 4MHz, and we provide a clock divider factor CD such that baud rate = MCK/(16*CD)
	//Therefore we need a clock divide coefficient of 26, which provides a baud rate of 9615 baud. This 0.1% error is accounted for by the receiving UART
	uartInit(4, 13);
		
    /* Replace with your application code */
    while (1) 
    {
		//wait for the ESP8266 to send a request. Requests take the form 'REQ:<tag>/REQ', with TAG being <= 10 characters. Therefore the request[] array must be able to contain 18 characters
		
		char request[BUFF_LEN] = "                  "; //initializing to a known value
		int  charIndex = 0;
		while (requestInString(request) == -1) {
			// Loop if we run out of space
			if (charIndex >= BUFF_LEN) charIndex = 0;
			
			//wait for a complete request to be transmitted before processing
			while (!uartRxReady());
			request[charIndex++] = uartRx();
		}
		
		//the request has been received. now process to determine whether to turn the LED on or off
		if (inString(request, "ledon")) {
			pioDigitalWrite(LED_PIN, PIO_HIGH);
		}
		if (inString(request, "ledoff")) {
			pioDigitalWrite(LED_PIN, PIO_LOW);
		}
		
		//next, read the RTC and create a string representation of the current time.
		char currtime[] = "12:34:56";
		
		char temperature[] = "70f";
		char humidity[] = "30%";
		
		//finally, transmit the webpage over UART
		//transmitting the first section of the webpage
		sendString(webpageStart);
		
		sendString(microcontrollerTimeStr);
		sendString(currtime);
		
		sendString(ledStr);
		
		sendString(temperatureStr);
		sendString(temperature);
		
		sendString(humidityStr);
		sendString(humidity);
		
		sendString(webpageEnd);
		
		
		
    }
}

void sendString(char* str) {
	char* ptr = str;
	while (*ptr) uartTx(*ptr++);
}

//determines whether a given character sequence is in a char array request, returning 1 if present, -1 if not present
int inString(char request[], char des[]) {
	if (strstr(request, des) != NULL) {return 1;}
	return -1;
}

//determines if tags "REQ:" and "/REQ" are in the input string
int requestInString(char request[]) {
	int tag1InString = inString(request, "/REQ:");
	if(tag1InString > 0) {
		return 1;
	}
	return -1;
}
