/*
 * GccApplication1.c
 *
 * Created: 11/12/2018 7:54:07 PM
 * Author : kaveh
 */ 


//WORKING

#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    //SystemInit();
	*(int *)0x20000008 = 2;
    /* Replace with your application code */
	REG_PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//now we enable the clock for peripheral #11 (PIOA p50)
	REG_PMC_PCER0 = PMC_PCER0_PID11; 
	//and enable the clock for peripheral #21 (SPI)
	REG_PMC_PCER0 = PMC_PCER0_PID21;
	//we next set the SPI pins as belonging to peripheral A (SPI) for PA11-PA14 (SPI pins)
	//first need to disable write protection (P633)
	REG_PIOA_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//now we set PA11-PA14 to outside PIO contorl
	REG_PIOA_PDR = PIO_PDR_P11;
	REG_PIOA_PDR = PIO_PDR_P12;
	REG_PIOA_PDR = PIO_PDR_P13;
	REG_PIOA_PDR = PIO_PDR_P14;
	//PA11-14 are automatically initialized to PIO_ABCD0/1 = 0,0, so they will be by default assigned to peripheral A which is SPI
	//we next move to the SPI interface 
	//disabling write protection
	REG_SPI_WPMR = SPI_WPMR_WPKEY_PASSWD;
	//Enabling SPI
	REG_SPI_CR = 0x00000001; //p600, SPI enabled
	//Configuring SPI to master mode (p601)
	//master mode
	//fixed peripheral select
	//chip select lines directly connected to peripheral device
	//mode fault detection enabled
	//WDRBT disabled
	//LLB disabled
	//PCS = 0000 (Peripheral 0 selected), means NPCS[3:0] = 1110
	REG_SPI_MR = 0x00000001;
	//We next set up the chip select register for peripheral 0 (CSR is chip select register 0)
	REG_SPI_CSR = 0x0000FF00; //test settings
	char toSend = 0;
	char toSendArr[] = {0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    while (1) 
    {
	//we now write to the SPI register
	//REG_SPI_TDR = 0x00000000;
	char received = *(int*) 0x40008008;
	REG_SPI_TDR = toSendArr[toSend];
	toSend++;
	if (toSend > 11) {toSend = 0;}
	for(int i = 0; i < 3000; i++) {
		}
	}
	
}
