//Kaveh Pezeshki
//literally just turns an LED on

#include "easySamIO.h"

int main(void) {
	samInit();
	pinMode(10, OUTPUT);
	while (1) {
		digitalWrite(10, HIGH);
		for(int i = 0; i < 1000; i++);
		digitalWrite(10, LOW);
		for(int i = 0; i < 1000; i++);
	}
}

		
	