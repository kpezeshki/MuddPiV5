/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	sysclk_init();
	//board_init();
	
	WDT->WDT_MR = WDT_MR_WDDIS;                         // disable watchdog
	ioport_init();                                      // call before using IOPORT service
	ioport_set_pin_dir(16, IOPORT_DIR_OUTPUT);        // LED pin set as output
	ioport_set_pin_level(16, IOPORT_PIN_LEVEL_HIGH);  // switch LED off

	/* Insert application code here, after the board has been initialized. */
	while (1) {
		ioport_toggle_pin_level(16);
		delay_ms(1000);
	}
}