/*
 * uartTest.c
 *
 * Created: 12/9/2018 7:21:32 PM
 * Author : kaveh
 */ 

#include "easySamIO.h"
#include <string.h>
#define LED_PIN 17
#define STATUS_PIN 18

const char* webpageStart = "<!DOCTYPE html><html>\n    <head>\n        <title>E155 Web Server Demo Webpage</title>\n        <meta http-equiv=\"refresh\" content=\"5\">\n    </head>\n    <body>\n        <h1>E155 Web Server Demo Webpage</h1>\n        <p>Current Microcontroller Time:</p>\n        ";
const char* webpageEnd   = "\n        <p>LED Control:</p>\n        <form action=\"ledon\">\n            <input type=\"submit\" value=\"Turn the LED on!\" />\n        </form>\n        <form action=\"ledoff\">\n                <input type=\"submit\" value=\"Turn the LED off!\" />\n        </form>\n    </body>\n</html>\n";
const int webpageStartChars = 255;
const int webpageEndChars = 270;

int main(void) {
    /* Initialize the SAM system */
	samInit();
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	pinMode(STATUS_PIN, OUTPUT);
	digitalWrite(STATUS_PIN, HIGH);
	uartInit(4, 25);
    /* Replace with your application code */
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
		currentRxState = ((REG_UART_SR) & 1);
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
				digitalWrite(STATUS_PIN, LOW);
				//two options: ON and OFF
				int ledOnInString = strstr(request, "ON");
				int ledOffInString = strstr(request, "OFF");
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
				digitalWrite(STATUS_PIN, HIGH);
				
			}
			currentRequestChar += 1;
		}	
			
    }
}

void transmitWebpage() {
	for (int charCount = 0; charCount < webpageStartChars; charCount++) {
		uartTx(webpageStart[charCount]);
		if (webpageStart[charCount] == '\n') {uartTx('\r');}
	}
	for (int charCount = 0; charCount < webpageEndChars; charCount++) {
		uartTx(webpageEnd[charCount]);
		if (webpageEnd[charCount] == '\n') {uartTx('\r');}
	}	
}

//documentation print statements
/*uartTx('O');
uartTx('F');
uartTx('F');
uartTx('\n');
uartTx('\r');*/
/*uartTx('R');
uartTx('Q');
uartTx('\n');
uartTx('\r');*/
/*uartTx('O');
uartTx('N');
uartTx('\n');
uartTx('\r');*/
/*if (endInString != 0) {
uartTx('E');
uartTx('I');
uartTx('\n');
uartTx('\r');
}*/
/*if (startInString != 0) {
uartTx('S');
uartTx('I');
uartTx('\n');
uartTx('\r');
}*/
		/*uartTx(character);
uartTx('\n');
uartTx('\r');
for (int i = 0; i < 14; i++) {
uartTx(request[i]);
}
uartTx('\n');
uartTx('\r');*/