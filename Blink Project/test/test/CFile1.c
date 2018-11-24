/*
 * test.c
 *
 * Created: 11/9/2018 11:37:13 PM
 * Author : Chris
 */ 

#include <asf.h>

int main(void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	WDT->WDT_MR = WDT_MR_WDDIS;                         // disable watchdog
	ioport_init();                                      // call before using IOPORT service
	ioport_set_pin_dir(18, IOPORT_DIR_OUTPUT);        // LED pin set as output
	ioport_set_pin_level(18, IOPORT_PIN_LEVEL_HIGH);  // switch LED off

	/* Insert application code here, after the board has been initialized. */
	while (1) {
		ioport_toggle_pin_level(18);
		delay_ms(1000);
	}
}
