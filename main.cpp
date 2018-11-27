//Kaveh Pezeshki
//literally just turns an LED on

#include "easySamIO.h"
#include <stdio.h>

int main(void) {
	samInit();
	
	//Testing Digital I/O
	/*
	pinMode(10, OUTPUT);
	while (1) {
		digitalWrite(10, LOW);
		for(int i = 0; i < 100000; i++);
		digitalWrite(10, HIGH);
		for(int i = 0; i < 100000; i++);
	}*/
	
	
	//Testing SPI and UART
	unsigned short received = 0;
	float voltage;
	spiInit(255, 0, 0);
	uartInit(4,2);
	char strTransmit[5];
	
	while (1) {
		received = spiSendReceive16(0x6000);
		received &= 0x03FF; //removing top 6 bits
		voltage = 3.3*((float)received/1023.0);

		snprintf(strTransmit, 5, "%f", voltage);
		
		for (int charNum = 0; charNum < 5; charNum++) {
			uartTx(strTransmit[charNum]);
		}
		
	}
}	