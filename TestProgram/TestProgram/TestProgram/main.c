/*
 * TestProgram.c
 *
 * Created: 11/3/2018 10:21:20 PM
 * Author : kaveh
 */ 


#include "asf.h"
#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	/* Initializing GPIO */
	ioport_init();

    /* Replace with your application code */
	int i = 0;
	
    while (1) 
    {
		ioport_toggle_pin_level
    }
}
