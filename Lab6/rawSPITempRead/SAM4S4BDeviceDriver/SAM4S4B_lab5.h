volatile unsigned long* WDT_MR = (unsigned long*) 0x400E1454; // Pointer to the WDT_MR register
*WDT_MR |= 1 << 15; // Sets the WDDIS bit to 1 to disable the watchdog timer

volatile unsigned long* PMC_PCER0 = (unsigned long*) 0x400E0410; // Pointer to the PMC_PVER0 register
*PMC_PCER0 |= 1 << 11; // Enables PIOA
*PMC_PCER0 |= 1 << 12; // Enables PIOB
