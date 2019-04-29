/*
 * sam_backend.c
 *
 * Created: 12/7/2018 5:18:33 PM
 * Author : Kaveh Pezeshki and Chris Ferrarin and Erik Meike
 * 
 * MCU backend for Lab 6. Generates webpages as requested by the ESP8266, and interfaces with the onboard PIO and ADC peripherals to allow user control of an LED and to display the current time.
 * 
 */ 


#include "SAM4S4BDeviceDriver\SAM4S4B.h"
#include <string.h>

#define LED_PIN 18
#define BUFF_LEN 32

//Defining the web page in several chunks: everything before the current time, and everything after the current time
//Please see the e155 website for a human-readable version of the file "webpage.html"

const char* webpageStart = "<!DOCTYPE html><html><head><title>E155 Web Server Demo Webpage</title><meta http-equiv=\"refresh\" content=\"5\"></head><body><h1>E155 Web Server Demo Webpage</h1>";
const char* microcontrollerTimeStr = "<p>Current Microcontroller Time:</p>";
const char* ledStr = "<p>LED Control:</p><form action=\"ledon\"><input type=\"submit\" value=\"Turn the LED on!\" /></form> <form action=\"ledoff\"><input type=\"submit\" value=\"Turn the LED off!\" /></form>";
const char* temperatureStr = "<p>Current Temperature:</p>";
const char* humidityStr = "<p>Current Humidity:</p>";
const char* webpageEnd   = "</body></html>";


// Pressure sensor constants

volatile double temp = 0;
volatile double press = 0;
volatile char id = 0;

/////////////////////////////////////////////////////////////////
// Pressure Sensor Provided Constants and Functions
/////////////////////////////////////////////////////////////////
const unsigned short dig_T1 = 27504;
const short dig_T2 = 26435;
const short dig_T3 = -1000;
const unsigned short dig_P1 = 36477;
const short dig_P2 = -10685;
const short dig_P3 = 3024;
const short dig_P4 = 2855;
const short dig_P5 = 140;
const short dig_P6 = -7;
const short dig_P7 = 15500;
const short dig_P8 = -14600;
const short dig_P9 = 6000;
const long signed int t_fine = 0;

// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
volatile double convertTemp (volatile char msb, volatile char lsb, volatile char xlsb) {
	volatile signed long adc_T = (msb << 12) | (lsb << 4) | xlsb;
	volatile double var1, var2, T;
	var1 = (((double) adc_T)/16384.0 - ((double) dig_T1)/1024.0) * ((double) dig_T2);
	var2 = ((((double )adc_T)/131072.0 - ((double) dig_T1)/8192.0) *
	(((double) adc_T)/131072.0 - ((double) dig_T1)/8192.0)) * ((double) dig_T3);
	t_fine = (long signed int) (var1 + var2);
	T = (var1 + var2) / 5120.0;
	return T;
}

// Returns pressure in Pa as double. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
volatile double convertPress (volatile char msb, volatile char lsb, volatile char xlsb) {
	volatile signed long adc_P = (msb << 12) | (lsb << 4) | xlsb;
	volatile double var1, var2, p;
	var1 = ((double) t_fine/2.0) - 64000.0;
	var2 = var1 * var1 * ((double) dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double) dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double) dig_P4) * 65536.0);
	var1 = (((double) dig_P3) * var1 * var1 / 524288.0 + ((double) dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double) dig_P1);
	if (var1 == 0.0) return 0; // Avoid exception caused by division by zero
	p = 1048576.0 - (double) adc_P;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double) dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double) dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double) dig_P7)) / 16.0;
	return p;
}

void BMP280Init(void)
{
	// Initialize BMP280
	pioDigitalWrite(CSB, PIO_LOW);
	spiSendReceive16(0x742F); // osrs_t = 001, osrs_p = 011, mode = 11
	spiSendReceive16(0x7510); // t_sb = 000, filter = 100, [0], spi3w_en = 0
	pioDigitalWrite(CSB, PIO_HIGH);

	// Confirm chip ID
	pioDigitalWrite(CSB, PIO_LOW);
	spiSendReceive(0xD0);
	id = spiSendReceive(0);
	pioDigitalWrite(CSB, PIO_HIGH);
}

void BMP280Read(void)
{
	// Receive pressure and temperature information over SPI
	pioDigitalWrite(CSB, PIO_LOW);
	spiSendReceive(0xF7);
	volatile char press_msb = spiSendReceive(0);
	volatile char press_lsb = spiSendReceive(0);
	volatile char press_xlsb = spiSendReceive(0);
	volatile char temp_msb = spiSendReceive(0);
	volatile char temp_lsb = spiSendReceive(0);
	volatile char temp_xlsb = spiSendReceive(0);
	pioDigitalWrite(CSB, PIO_HIGH);
	
	// Calculate final temp and pressure
	temp = convertTemp(temp_msb, temp_lsb, temp_xlsb);
	press = convertPress(press_msb, press_lsb, press_xlsb);
}

int main(void)
{
    //Initialize peripheral clocks
	samInit();
	pioInit();
	tcInit();
	tcDelayInit();

	// SPI init routines
	pioPinMode(CSB, PIO_OUTPUT);
	pioDigitalWrite(CSB, PIO_HIGH); // Either force the pin high initially or delay long enough for the pull-up resistor to respond
	spiInit(20, 1, 1); // Divide clock by 10 since max freq is 10 MHz. In (1, 1) mode.

	//Initialize GPIO pin  for LED control
	pioPinMode(LED_PIN, PIO_OUTPUT);
	pioDigitalWrite(LED_PIN, PIO_HIGH);

	//Initialize UART with no parity, 9600 baud
	//The peripheral clock is 4MHz, and we provide a clock divider factor CD such that baud rate = MCK/(16*CD)
	//Therefore we need a clock divide coefficient of 26, which provides a baud rate of 9615 baud. This 0.1% error is accounted for by the receiving UART
	//Therefore we need a clock divide coefficient of 13, which provides a baud rate of 19231 baud. This small error is accounted for by the receiving UART
	uartInit(4, 13);

	BMP280Init();
		
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
			
		BMP280Read();
		char temperature[20];
		char pressure[20];

		sprintf(temperature, "%f C", temp);
		sprintf(pressure, "%f kPa", press);
		
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
