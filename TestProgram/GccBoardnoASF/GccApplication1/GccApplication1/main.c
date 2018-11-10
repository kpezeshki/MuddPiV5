/*
 * GccApplication1.c
 *
 * Created: 11/9/2018 10:41:16 PM
 * Author : kaveh
 */ 


#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	//enable the peripheral clock
	//just an enable (doesn't care about writing 0), so we don't |=
	//from the peripherals table on P50 of the SAM4S datasheet PIOA has instance ID 11
	//first need to disable write protection
	//this is done by writing 0x504D43 (“PMC” in ASCII) to [31:8] in PMC write protection mode register, and 1 in bit 0 (page 554)
	PMC->PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//now we enable the clock for peripheral #11 (PIOA p50)
	PMC->PMC_PCER0 = PMC_PCER0_PID11; 
	
	//next we set the desired pin (PA26) as an output (P588)
	//first need to disable write protection (P633)
	PIOA->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//Now we set the PIO to control pin 26 (bit 26 of PIO_PER)
	//should we be using REG_PIOA_Per in pioa.h?
	PIOA->PIO_PER  = PIO_PER_P26;
	//we now set the LED high, by writing a 1 in pin 26 of PIO_OER
	PIOA->PIO_OER  = PIO_OER_P26;
	

    /* Replace with your application code */
    while (1) 
    {
    }
}
