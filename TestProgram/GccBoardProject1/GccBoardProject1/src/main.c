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
#include "board.h"
#define TESTPIN IOPORT_CREATE_PIN(PIOA, 9)
#define TESTPIN2 IOPORT_CREATE_PIN(PIOA, 25)

#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    (4000000U)
#define BOARD_FREQ_MAINCK_BYPASS  (4000000U)
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	ioport_init();
	ioport_set_pin_dir(TESTPIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TESTPIN2, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(TESTPIN2, IOPORT_MODE_PULLUP);
	bool value;
	while (1) {
		value = ioport_get_pin_level(TESTPIN2);
		ioport_set_pin_level(TESTPIN, value);
	}
	
}
