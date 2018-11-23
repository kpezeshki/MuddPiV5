// cferrarin@g.hmc.edu
// GPIO

#define LOW			 0
#define HIGH		 1

#define INPUT		 0
#define OUTPUT		 1
#define A			 2
#define B			 3
#define C			 4
#define D			 5

#define PMC			((volatile unsigned long *) 0x400E0400)
#define PMC_SCER	((volatile unsigned long *) (PMC + 0))
#define PMC_SCDR	((volatile unsigned long *) (PMC + 1))
#define PMC_SCSR	((volatile unsigned long *) (PMC + 2))
#define PMC_PCER0	((volatile unsigned long *) (PMC + 4))
#define PMC_PCDR0	((volatile unsigned long *) (PMC + 5))
#define PMC_PCSR0	((volatile unsigned long *) (PMC + 6))
#define PMC_WPMR	((volatile unsigned long *) (PMC + 57))

#define PIO         ((volatile unsigned long *) 0x400E0E00)
#define PIO_PER     ((volatile unsigned long *) (PIO + 0))
#define PIO_PDR     ((volatile unsigned long *) (PIO + 1))
#define PIO_PSR     ((volatile unsigned long *) (PIO + 2))
#define PIO_OER     ((volatile unsigned long *) (PIO + 4))
#define PIO_ODR     ((volatile unsigned long *) (PIO + 5))
#define PIO_OSR     ((volatile unsigned long *) (PIO + 6))
#define PIO_IFER    ((volatile unsigned long *) (PIO + 8))
#define PIO_IFDR    ((volatile unsigned long *) (PIO + 9))
#define PIO_IFSR    ((volatile unsigned long *) (PIO + 10))
#define PIO_SODR    ((volatile unsigned long *) (PIO + 12))
#define PIO_CODR    ((volatile unsigned long *) (PIO + 13))
#define PIO_ODSR    ((volatile unsigned long *) (PIO + 14))
#define PIO_PDSR    ((volatile unsigned long *) (PIO + 15))
#define PIO_IER     ((volatile unsigned long *) (PIO + 16))
#define PIO_IDR     ((volatile unsigned long *) (PIO + 17))
#define PIO_IMR     ((volatile unsigned long *) (PIO + 18))
#define PIO_ISR     ((volatile unsigned long *) (PIO + 19))
#define PIO_MDER    ((volatile unsigned long *) (PIO + 20))
#define PIO_MDDR    ((volatile unsigned long *) (PIO + 21))
#define PIO_MDSR    ((volatile unsigned long *) (PIO + 22))
#define PIO_PUDR    ((volatile unsigned long *) (PIO + 24))
#define PIO_PUER    ((volatile unsigned long *) (PIO + 25))
#define PIO_PUSR    ((volatile unsigned long *) (PIO + 26))
#define PIO_ABCDSR1 ((volatile unsigned long *) (PIO + 28))
#define PIO_ABCDSR2 ((volatile unsigned long *) (PIO + 29))
#define PIO_PPDDR   ((volatile unsigned long *) (PIO + 36))
#define PIO_PPDER   ((volatile unsigned long *) (PIO + 37))
#define PIO_PPDSR   ((volatile unsigned long *) (PIO + 38))
#define PIO_OWER    ((volatile unsigned long *) (PIO + 40))
#define PIO_OWDR    ((volatile unsigned long *) (PIO + 41))
#define PIO_OWSR    ((volatile unsigned long *) (PIO + 42))

void pioInit() {
	*PMC_PCER0 |= (0b111 << 11);
}

void pinMode(int pin, int function) {
	
	*PIO_IFDR  |=  (1 << pin);
	*PIO_IER   &= ~(1 << pin);
	*PIO_IDR   |=  (1 << pin);
	*PIO_MDER  &= ~(1 << pin);
	*PIO_MDDR  |=  (1 << pin);
	*PIO_PUER  &= ~(1 << pin);
	*PIO_PUDR  |=  (1 << pin);
	*PIO_PPDER &= ~(1 << pin);
	*PIO_PPDDR |=  (1 << pin);
	*PIO_OWER  &= ~(1 << pin);
	*PIO_OWDR  |=  (1 << pin);

	if (function == INPUT || function == OUTPUT) {
		*PIO_PER |=  (1 << pin);
		*PIO_PDR &= ~(1 << pin);
	} else {
		*PIO_PER &= ~(1 << pin);
		*PIO_PDR |=  (1 << pin);
	}

	switch (function) {
		case INPUT:
			*PIO_OER &= ~(1 << pin);
			*PIO_ODR |=  (1 << pin);
			break;
		case OUTPUT:
			*PIO_OER |=  (1 << pin);
			*PIO_ODR &= ~(1 << pin);
			break;
		case A:	
			*PIO_ABCDSR1 &= ~(1 << pin);
			*PIO_ABCDSR2 &= ~(1 << pin);
			break;
		case B:
			*PIO_ABCDSR1 |=  (1 << pin);
			*PIO_ABCDSR2 &= ~(1 << pin);
			break;
		case C:
			*PIO_ABCDSR1 &= ~(1 << pin);
			*PIO_ABCDSR2 |=  (1 << pin);
			break;
		case D:
			*PIO_ABCDSR1 |= (1 << pin);
			*PIO_ABCDSR2 |= (1 << pin);
			break;
		// Otherwise, do nothing
	}
}

void digitalWrite(int pin, int val) {
	if (val == HIGH) {
		*PIO_SODR |= (1 << pin);
	} else {
		*PIO_CODR |= (1 << pin);
	}
}

int digitalRead(int pin) {
	return (*PIO_PDSR >> pin) & 1;
}

void toggle(int pin) {
	int currentVal = digitalRead(pin);
	digitalWrite(pin, !currentVal);
}
