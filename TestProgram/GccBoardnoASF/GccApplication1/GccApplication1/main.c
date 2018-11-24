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
    //SystemInit();
	
	//enable the peripheral clock
	//just an enable (doesn't care about writing 0), so we don't |=
	//from the peripherals table on P50 of the SAM4S datasheet PIOA has instance ID 11
	//first need to disable write protection
	//this is done by writing 0x504D43 (“PMC” in ASCII) to [31:8] in PMC write protection mode register, and 1 in bit 0 (page 554)
	//PMC->PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//now we enable the clock for peripheral #11 (PIOA p50)
	//PMC->PMC_PCER0 = PMC_PCER0_PID11; 
	
	//next we set the desired pin (PA26) as an output (P588)
	//first need to disable write protection (P633)
	//PIOA->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//Now we set the PIO to control pin 26 (bit 26 of PIO_PER)
	//should we be using REG_PIOA_Per in pioa.h?
	//PIOA->PIO_PER  = PIO_PER_P26;
	//We now set pin 26 as an output, by writing a 1 in pin 26 of PIO_OER
	//PIOA->PIO_OER  = PIO_OER_P26;
	//We next write the LED to be high, by writing in PIO_SODR (set output data register), and can be cleared by writing in PIO_CODR (clear output data register). These results can be seen on PIO_ODSR (output data status register), which represents the current state of the output pins
	//An overview is on p573
	//PIOA->PIO_CODR = PIO_CODR_P26;
	
	//we test writing to address 0x22000000
	*(int *)0x20000008 = 1;
	int i = 0;


    /* Replace with your application code */
    while (1) 
    {
		i = i + 1;
		/*
				//enable the peripheral clock
	//just an enable (doesn't care about writing 0), so we don't |=
	//from the peripherals table on P50 of the SAM4S datasheet PIOA has instance ID 11
	//first need to disable write protection
	//this is done by writing 0x504D43 (“PMC” in ASCII) to [31:8] in PMC write protection mode register, and 1 in bit 0 (page 554)
	REG_PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//now we enable the clock for peripheral #11 (PIOA p50)
	REG_PMC_PCER0 = PMC_PCER0_PID11; 
	
	//next we set the desired pin (PA26) as an output (P588)
	//first need to disable write protection (P633)
	REG_PIOA_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//Now we set the PIO to control pin 26 (bit 26 of PIO_PER)
	//should we be using REG_PIOA_Per in pioa.h?
	REG_PIOA_PER  = PIO_PER_P26;
	//We now set pin 26 as an output, by writing a 1 in pin 26 of PIO_OER
	REG_PIOA_OER  = PIO_OER_P26;
	//We next write the LED to be high, by writing in PIO_SODR (set output data register), and can be cleared by writing in PIO_CODR (clear output data register). These results can be seen on PIO_ODSR (output data status register), which represents the current state of the output pins
	//An overview is on p573
	REG_PIOA_CODR = PIO_CODR_P26;
	
	//currentstatus = PIOA->PIO_ODSR; */
    }
}
