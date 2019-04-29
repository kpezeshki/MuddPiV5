// Chris Ferrarin
// Note: PA17 LED is broken on my board; use PA18 instead.

#include "SAM4S4BDeviceDriver/SAM4S4B.h"
#include <stdio.h>

#define CSB PIO_PA10
#define LED PIO_PA18

volatile double temp = 0;
volatile double press = 0;
volatile char id = 0;

/////////////////////////////////////////////////////////////////
// Provided Constants and Functions
/////////////////////////////////////////////////////////////////
unsigned short dig_T1 = 27504;
short dig_T2 = 26435;
short dig_T3 = -1000;
unsigned short dig_P1 = 36477;
short dig_P2 = -10685;
short dig_P3 = 3024;
short dig_P4 = 2855;
short dig_P5 = 140;
short dig_P6 = -7;
short dig_P7 = 15500;
short dig_P8 = -14600;
short dig_P9 = 6000;
long signed int t_fine = 0;

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


/////////////////////////////////////////////////////////////////
// User Code
/////////////////////////////////////////////////////////////////

int main(void) {
	// Setup
	samInit();
	pioInit();
	tcInit();
	tcDelayInit();
	pioPinMode(CSB, PIO_OUTPUT);
	pioPinMode(LED, PIO_OUTPUT);
	pioDigitalWrite(CSB, PIO_HIGH); // Either force the pin high initially or delay long enough for the pull-up resistor to respond
	spiInit(20, 1, 1); // Divide clock by 10 since max freq is 10 MHz. In (1, 1) mode.
	
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
		
	while (1) {
		pioTogglePin(LED);
		
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
	return 0;
}
