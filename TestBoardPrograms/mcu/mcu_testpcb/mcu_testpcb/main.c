/*
 * mcu_testpcb.c
 *
 * Created: 1/31/2019 12:05:33 AM
 * Author : Kaveh Pezeshki
 */ 


#include "SAM4S4B.h"


int main(void)
{
	/* Initializing the system */
	//sets up peripheral IO controllers and PCK2 peripheral clock at 1MHz.
	//this is the peripheral clock supplied to the FPGA
	samInit(); 

    /* Replace with your application code */
    while (1) 
    {
	//the application doesn't do anything else.
	//if a peripheral clock is supplied to the FPGA, the microcontroller is working.
    }
}
