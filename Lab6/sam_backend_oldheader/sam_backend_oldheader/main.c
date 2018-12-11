/*
 * uartTest.c
 *
 * Created: 12/9/2018 7:21:32 PM
 * Author : kaveh
 */ 

#include "easySamIO2.h"
#include <string.h>
#include <stdio.h>
#include <stdio_ext.h>
#define LED_PIN 17
#define TRANSMIT_PIN 18

const char* webpageStart = "<!DOCTYPE html><html>\n    <head>\n        <title>E155 Web Server Demo Webpage</title>\n        <meta http-equiv=\"refresh\" content=\"120\">\n    </head>\n    <body>\n        <h1>E155 Web Server Demo Webpage</h1>\n        <p>Current Microcontroller Time:</p>\n        ";
const char* webpageEnd   = "\n        <p>LED Control:</p>\n        <form action=\"on\">\n            <input type=\"submit\" value=\"Turn the LED on!\" />\n        </form>\n        <form action=\"off\">\n                <input type=\"submit\" value=\"Turn the LED off!\" />\n        </form>\n    </body>\n</html>\n";
const int webpageStartChars = 257;
const int webpageEndChars = 264;

int main(void) {
    /* Initialize the SAM system */
	samInit();
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	pinMode(TRANSMIT_PIN, OUTPUT);
	digitalWrite(TRANSMIT_PIN, HIGH);
	uartInit(4, 25);
	adcInit(0);
	adcChannelInit(CH2, 0, 0);
	
	int currentRxState = 0;
	char character;
	char request[14] = "               ";
	int requestFound = 0;
	int currentRequestChar = 0;
	int startInString = 0;
	int endInString = 0;
	const char requestStart = 0x3c;
	const char requestEnd = 0x3e;

	transmitWebpage();
	
	
	
    while (1) 
    {
		//checking whether a byte is available
		currentRxState = UART_REGS->UART_SR.RXRDY;
		//testing string checking
		if (currentRxState == 1) { //if there is a character to read
			if(currentRequestChar == 14) {
				currentRequestChar = 0;
			}
			character = uartRx();
			request[currentRequestChar] = character;
			//searching for substring
			int startInString = strchr(request, requestStart);
			int endInString   = strchr(request, requestEnd);
			//resetting after the initial request is sent
			if (startInString != 0 && currentRequestChar >= 2 && request[0] != requestStart) {
				request[0] = '<';
				for (int i = 1; i < 14; i++) {
					request[i] = ' ';
				}
				currentRequestChar = 0;
			}
			//processing webpage if both start and end in string
			if (startInString != 0 && endInString != 0) {
				//two options: ON and OFF
				int ledOnInString = strstr(request, "on");
				int ledOffInString = strstr(request, "off");
				if(ledOnInString != 0) {

					digitalWrite(LED_PIN, LOW);
				}
				if(ledOffInString != 0) {
					digitalWrite(LED_PIN, HIGH);
				}
				//clear request
				for (int i = 0; i < 14; i++) {
					request[i] = ' ';
				}
				//transmitting webpage
				transmitWebpage();				
			}
			currentRequestChar += 1;
		}	
			
    }
}

void transmitWebpage() {
	digitalWrite(TRANSMIT_PIN, LOW);
	for (int charCount = 0; charCount < webpageStartChars; charCount++) {
		uartTx(webpageStart[charCount]);
		if (webpageStart[charCount] == '\n') {uartTx('\r');}
	}
	
	//reading the ADC
	float ch2Voltage;
	char ch2VoltageStr[5];
	ch2Voltage = adcRead(CH2);
	//converting to a string
	snprintf(ch2VoltageStr, 5, "%f", 5555);
	for (int charCount = 0; charCount < webpageEndChars; charCount++) {
		uartTx(webpageEnd[charCount]);
		if (webpageEnd[charCount] == '\n') {uartTx('\r');}
	}	
	digitalWrite(TRANSMIT_PIN, HIGH);
}


char[] floatToString(float input) {
	
}