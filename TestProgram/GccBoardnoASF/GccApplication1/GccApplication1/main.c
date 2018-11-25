/*
 * GccApplication1.c
 *
 * Created: 11/12/2018 7:54:07 PM
 * Author : kaveh
 */ 


//WORKING

//#include "sam.h"
//#include "easySamIO.h"

int main(void)
{
	/*

	REG_PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//now we enable the clock for peripheral #11 (PIOA p50)
	REG_PMC_PCER0 = 1<<11; 
	
	//next we set the desired pin (PA26) as an output (P588)
	//first need to disable write protection (P633)
	REG_PIOA_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//Now we set the PIO to control pin 26 (bit 26 of PIO_PER)
	//should we be using REG_PIOA_Per in pioa.h?
	REG_PIOA_PER  = 1<<10;
	//We allow the PIO write access to pin 26
	REG_PIOA_OWER = 1<<10;
	//We now set pin 26 as an output, by writing a 1 in pin 26 of PIO_OER
	REG_PIOA_OER  = 1<<10;
	//We next write the LED to be high, by writing in PIO_SODR (set output data register), and can be cleared by writing in PIO_CODR (clear output data register). These results can be seen on PIO_ODSR (output data status register), which represents the current state of the output pins
	//An overview is on p573
	REG_PIOA_ODSR = 0; //PIO_ODSR_P9;
    while (1) 
    {
	REG_PIOA_CODR = 1<<10; //SETS LED LOW
	REG_PIOA_SODR = 1<<10; //SETS LED HIGH
	}*/
	
	while(1) {
	*(int *)0x20000008 = 2; }
	
}
