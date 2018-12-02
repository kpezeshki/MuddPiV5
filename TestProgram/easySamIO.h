// cferrarin@g.hmc.edu
// kpezeshki@g.hmc.edu
// 11/26/2018

// all page numbers reference the SAM4S Series Datasheet as of 11/26/2018

/* This header file simplifies peripheral memory access for the ATSAM4S4B for four peripherals:
   1) PMC (Power Management Controller): Controls embeddded system and peripheral clocks. (p418)
      In order to use a peripheral, we need to enable its clock in the PMC. p(421)
   2) PIO (Parallel I/O Controller): Provides basic GPIO access (turning a pin on or off), or maps GPIO to other peripherals (p467). We implement PIOA here.
   3) UART (Universal Asynchronous Receiver/Transmitter): A generic serial controller (p657)
   4) SPI (Serial Peripheral Interface): Onboard SPI controller (p582)
   5) Timer / Counter: Onboard timer and counter controller (p744)

    Before using any of these peripherals, we highly suggest that you read the relevant section in the datasheet. 
    We've implemented a bare minimum of configurability and functionality to support the labs, but each peripheral offers many more features that may prove useful in the final project.
*/

/* Development checklist:
 * PIO:   Add support for PIOB              DONE
 * PIO:   Final pass                        DONE
 * TIMER: Add support for TC1               DONE
 * TIMER: Refine delays, add delay_us()     DONE
 * TIMER: Final pass                        DONE
 * PMC:   Add support for FPGA clock        NOT STARTED
 * PMC:   Final pass                        NOT STARTED
 * SPI:   Fix "PCK" issue                   NOT STARTED
 * SPI:   Final pass                        NOT STARTED
 * UART:  Final pass                        NOT STARTED
 * PWM:   Add base support                  NOT STARTED
 * PWM:   Test                              NOT STARTED
 * PWM:   Final pass                        NOT STARTED
 * ADC:   Add base support                  NOT STARTED
 * ADC:   Test                              NOT STARTED
 * ADC:   Final pass                        NOT STARTED
 * All:   Final pass                        NOT STARTED
 */

//Constants taken from ATSAM4S4B CMSIS Library
//Relevant code is available at http://packs.download.atmel.com/

#ifndef EASY_SAM_IO_H
#define EASY_SAM_IO_H

#include <stdint.h>

/////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////

#define MCK        4000000

/////////////////////////////////////////////////////////////////////
// Base Address Definitions
/////////////////////////////////////////////////////////////////////

#define SPI        (0x40008000U) /**< \brief (SPI       ) Base Address */
#define TC0        (0x40010000U) /**< \brief (TC0       ) Base Address */
#define TC1        (0x40014000U) /**< \brief (TC1       ) Base Address */
#define PWM        (0x40020000U) /**< \brief (PWM       ) Base Address */
#define PMC        (0x400E0400U) /**< \brief (PMC       ) Base Address */
#define UART0      (0x400E0600U) /**< \brief (UART0     ) Base Address */
#define PIOA       (0x400E0E00U) /**< \brief (PIOA      ) Base Address */
#define PIOB       (0x400E1000U) /**< \brief (PIOB      ) Base Address */

/////////////////////////////////////////////////////////////////////
// PMC (Power Management Controller) Registers
/////////////////////////////////////////////////////////////////////

#define REG_PMC_SCER            (0x400E0400U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR            (0x400E0404U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR            (0x400E0408U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0           (0x400E0410U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0           (0x400E0414U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0           (0x400E0418U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_MOR            (0x400E0420U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_MCFR           (0x400E0424U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR          (0x400E0428U) /**< \brief (PMC) PLLA Register */
#define REG_CKGR_PLLBR          (0x400E042CU) /**< \brief (PMC) PLLB Register */
#define REG_PMC_MCKR            (0x400E0430U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB             (0x400E0438U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_PCK             (0x400E0440U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER             (0x400E0460U) /**< \brief (PMC) Interrupt Enable Register */
#define REG_PMC_IDR             (0x400E0464U) /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR              (0x400E0468U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR             (0x400E046CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_FSMR            (0x400E0470U) /**< \brief (PMC) Fast Startup Mode Register */
#define REG_PMC_FSPR            (0x400E0474U) /**< \brief (PMC) Fast Startup Polarity Register */
#define REG_PMC_FOCR            (0x400E0478U) /**< \brief (PMC) Fault Output Clear Register */
#define REG_PMC_WPMR            (0x400E04E4U) /**< \brief (PMC) Write Protect Mode Register */
#define REG_PMC_WPSR            (0x400E04E8U) /**< \brief (PMC) Write Protect Status Register */
#define REG_PMC_PCER1           (0x400E0500U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
#define REG_PMC_PCDR1           (0x400E0504U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
#define REG_PMC_PCSR1           (0x400E0508U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
#define REG_PMC_OCR             (0x400E0510U) /**< \brief (PMC) Oscillator Calibration Register */

#define PMC_WPMR_WPKEY_PASSWD           (0x504D43u << 8) /**< \brief (PMC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// PIO (Parallel Input/Output) Registers
/////////////////////////////////////////////////////////////////////

#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7
#define PA8     8
#define PA9     9
#define PA10    10
#define PA11    11
#define PA12    12
#define PA13    13
#define PA14    14
#define PA15    15
#define PA16    16
#define PA17    17
#define PA18    18
#define PA19    19
#define PA20    20
#define PA21    21
#define PA22    22
#define PA23    23
#define PA24    24
#define PA25    25
#define PA26    26
#define PA27    27
#define PA28    28
#define PA29    29
#define PA30    30
#define PA31    31
#define PB0     32
#define PB1     33
#define PB2     34
#define PB3     35
#define PB4     36
#define PB5     37
#define PB6     38
#define PB7     39
#define PB8     40
#define PB9     41
#define PB10    42
#define PB11    43
#define PB12    44
#define PB13    45
#define PB14    46

typedef struct {
    uint32_t PIO_PER;        /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
    uint32_t PIO_PDR;        /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
    uint32_t PIO_PSR;        /**< \brief (Pio Offset: 0x0008) PIO Status Register */
    uint32_t Reserved1[1];
    uint32_t PIO_OER;        /**< \brief (Pio Offset: 0x0010) Output Enable Register */
    uint32_t PIO_ODR;        /**< \brief (Pio Offset: 0x0014) Output Disable Register */
    uint32_t PIO_OSR;        /**< \brief (Pio Offset: 0x0018) Output Status Register */
    uint32_t Reserved2[1];
    uint32_t PIO_IFER;       /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
    uint32_t PIO_IFDR;       /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
    uint32_t PIO_IFSR;       /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
    uint32_t Reserved3[1];
    uint32_t PIO_SODR;       /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
    uint32_t PIO_CODR;       /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
    uint32_t PIO_ODSR;       /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
    uint32_t PIO_PDSR;       /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
    uint32_t PIO_IER;        /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
    uint32_t PIO_IDR;        /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
    uint32_t PIO_IMR;        /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
    uint32_t PIO_ISR;        /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
    uint32_t PIO_MDER;       /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
    uint32_t PIO_MDDR;       /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
    uint32_t PIO_MDSR;       /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
    uint32_t Reserved4[1];
    uint32_t PIO_PUDR;       /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
    uint32_t PIO_PUER;       /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
    uint32_t PIO_PUSR;       /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
    uint32_t Reserved5[1];
    uint32_t PIO_ABCDSR1;  /**< \brief (Pio Offset: 0x0070) Peripheral Select Register 1 */
    uint32_t PIO_ABCDSR2;  /**< \brief (Pio Offset: 0x0074) Peripheral Select Register 2 */
    uint32_t Reserved6[2];
    uint32_t PIO_IFSCDR;     /**< \brief (Pio Offset: 0x0080) Input Filter Slow Clock Disable Register */
    uint32_t PIO_IFSCER;     /**< \brief (Pio Offset: 0x0084) Input Filter Slow Clock Enable Register */
    uint32_t PIO_IFSCSR;     /**< \brief (Pio Offset: 0x0088) Input Filter Slow Clock Status Register */
    uint32_t PIO_SCDR;       /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
    uint32_t PIO_PPDDR;      /**< \brief (Pio Offset: 0x0090) Pad Pull-down Disable Register */
    uint32_t PIO_PPDER;      /**< \brief (Pio Offset: 0x0094) Pad Pull-down Enable Register */
    uint32_t PIO_PPDSR;      /**< \brief (Pio Offset: 0x0098) Pad Pull-down Status Register */
    uint32_t Reserved7[1];
    uint32_t PIO_OWER;       /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
    uint32_t PIO_OWDR;       /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
    uint32_t PIO_OWSR;       /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
    uint32_t Reserved8[1];
    uint32_t PIO_AIMER;      /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
    uint32_t PIO_AIMDR;      /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
    uint32_t PIO_AIMMR;      /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
    uint32_t Reserved9[1];
    uint32_t PIO_ESR;        /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
    uint32_t PIO_LSR;        /**< \brief (Pio Offset: 0x00C4) Level Select Register */
    uint32_t PIO_ELSR;       /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
    uint32_t Reserved10[1];
    uint32_t PIO_FELLSR;     /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
    uint32_t PIO_REHLSR;     /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
    uint32_t PIO_FRLHSR;     /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
    uint32_t Reserved11[1];
    uint32_t PIO_LOCKSR;     /**< \brief (Pio Offset: 0x00E0) Lock Status */
    uint32_t PIO_WPMR;       /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
    uint32_t PIO_WPSR;       /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
    uint32_t Reserved12[5];
    uint32_t PIO_SCHMITT;    /**< \brief (Pio Offset: 0x0100) Schmitt Trigger Register */
    uint32_t Reserved13[19];
    uint32_t PIO_PCMR;       /**< \brief (Pio Offset: 0x150) Parallel Capture Mode Register */
    uint32_t PIO_PCIER;      /**< \brief (Pio Offset: 0x154) Parallel Capture Interrupt Enable Register */
    uint32_t PIO_PCIDR;      /**< \brief (Pio Offset: 0x158) Parallel Capture Interrupt Disable Register */
    uint32_t PIO_PCIMR;      /**< \brief (Pio Offset: 0x15C) Parallel Capture Interrupt Mask Register */
    uint32_t PIO_PCISR;      /**< \brief (Pio Offset: 0x160) Parallel Capture Interrupt Status Register */
    uint32_t PIO_PCRHR;      /**< \brief (Pio Offset: 0x164) Parallel Capture Reception Holding Register */
    uint32_t PIO_RPR;        /**< \brief (Pio Offset: 0x168) Receive Pointer Register */
    uint32_t PIO_RCR;        /**< \brief (Pio Offset: 0x16C) Receive Counter Register */
    uint32_t Reserved14[2];
    uint32_t PIO_RNPR;       /**< \brief (Pio Offset: 0x178) Receive Next Pointer Register */
    uint32_t PIO_RNCR;       /**< \brief (Pio Offset: 0x17C) Receive Next Counter Register */
    uint32_t Reserved15[2];
    uint32_t PIO_PTCR;       /**< \brief (Pio Offset: 0x188) Transfer Control Register */
    uint32_t PIO_PTSR;       /**< \brief (Pio Offset: 0x18C) Transfer Status Register */
} Pio;

#define PIO_WPMR_WPKEY_PASSWD (0x50494Fu << 8) /**< \brief (PIO_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// TC (Timer Counter) Registers
/////////////////////////////////////////////////////////////////////

typedef struct {
    uint32_t CLKEN   : 1;
    uint32_t CLKDIS  : 1;
    uint32_t SWTRG   : 1;
    uint32_t         : 29;
} TC_CCR_bits;

typedef struct {
    uint32_t TCCLKS  : 3;
    uint32_t CLKI    : 1;
    uint32_t BURST   : 2;
    uint32_t CPCSTOP : 1;
    uint32_t CPCDIS  : 1;
    uint32_t EEVTEDG : 2;
    uint32_t EEVT    : 2;
    uint32_t ENETRG  : 1;
    uint32_t WAVESEL : 2;
    uint32_t WAVE    : 1;
    uint32_t ACPA    : 2;
    uint32_t ACPC    : 2;
    uint32_t AEEVT   : 2;
    uint32_t ASWTRG  : 2;
    uint32_t BCPB    : 2;
    uint32_t BCPC    : 2;
    uint32_t BEEVT   : 2;
    uint32_t BSWTRG  : 2;
} TC_CMR_bits;

typedef struct {
    uint32_t COVFS   : 1;
    uint32_t LOVRS   : 1;
    uint32_t CPAS    : 1;
    uint32_t CPBS    : 1;
    uint32_t CPCS    : 1;
    uint32_t LDRAS   : 1;
    uint32_t LDRBS   : 1;
    uint32_t ETRGS   : 1;
    uint32_t         : 8;
    uint32_t CLKSTA  : 1;
    uint32_t MTIOA   : 1;
    uint32_t MTIOB   : 1;
    uint32_t         : 13;
} TC_SR_bits;

/** \brief TcChannel hardware registers */
typedef struct {
    TC_CCR_bits TC_CCR;        /**< \brief (TcChannel Offset: 0x0) Channel Control Register */
    TC_CMR_bits TC_CMR;        /**< \brief (TcChannel Offset: 0x4) Channel Mode Register */
    uint32_t    TC_SMMR;       /**< \brief (TcChannel Offset: 0x8) Stepper Motor Mode Register */
    uint32_t    Reserved1[1];
    uint32_t    TC_CV;         /**< \brief (TcChannel Offset: 0x10) Counter Value */
    uint32_t    TC_RA;         /**< \brief (TcChannel Offset: 0x14) Register A */
    uint32_t    TC_RB;         /**< \brief (TcChannel Offset: 0x18) Register B */
    uint32_t    TC_RC;         /**< \brief (TcChannel Offset: 0x1C) Register C */
    TC_SR_bits  TC_SR;         /**< \brief (TcChannel Offset: 0x20) Status Register */
    uint32_t    TC_IER;        /**< \brief (TcChannel Offset: 0x24) Interrupt Enable Register */
    uint32_t    TC_IDR;        /**< \brief (TcChannel Offset: 0x28) Interrupt Disable Register */
    uint32_t    TC_IMR;        /**< \brief (TcChannel Offset: 0x2C) Interrupt Mask Register */
    uint32_t    Reserved2[4];
} TcChannel;

/** \brief Tc hardware registers */
#define TCCHANNEL_NUMBER 3
typedef struct {
    TcChannel  TC_CHANNEL[TCCHANNEL_NUMBER]; /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */
    uint32_t TC_BCR;        /**< \brief (Tc Offset: 0xC0) Block Control Register */
    uint32_t TC_BMR;        /**< \brief (Tc Offset: 0xC4) Block Mode Register */
    uint32_t TC_QIER;       /**< \brief (Tc Offset: 0xC8) QDEC Interrupt Enable Register */
    uint32_t TC_QIDR;       /**< \brief (Tc Offset: 0xCC) QDEC Interrupt Disable Register */
    uint32_t TC_QIMR;       /**< \brief (Tc Offset: 0xD0) QDEC Interrupt Mask Register */
    uint32_t TC_QISR;       /**< \brief (Tc Offset: 0xD4) QDEC Interrupt Status Register */
    uint32_t TC_FMR;        /**< \brief (Tc Offset: 0xD8) Fault Mode Register */
    uint32_t Reserved1[2];
    uint32_t TC_WPMR;       /**< \brief (Tc Offset: 0xE4) Write Protect Mode Register */
} Tc;

#define TC_WPMR_WPKEY_PASSWD (0x54494Du << 8) /**< \brief (TC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


//SPI

#define REG_SPI_CR   (*(  volatile unsigned int *)0x40008000U) /**< \brief (SPI) Control Register */
#define REG_SPI_MR   (*(  volatile unsigned int *)0x40008004U) /**< \brief (SPI) Mode Register */
#define REG_SPI_RDR  (*(  volatile unsigned int *)0x40008008U) /**< \brief (SPI) Receive Data Register */
#define REG_SPI_TDR  (*(  volatile unsigned int *)0x4000800CU) /**< \brief (SPI) Transmit Data Register */
#define REG_SPI_SR   (*(  volatile unsigned int *)0x40008010U) /**< \brief (SPI) Status Register */
#define REG_SPI_IER  (*(  volatile unsigned int *)0x40008014U) /**< \brief (SPI) Interrupt Enable Register */
#define REG_SPI_IDR  (*(  volatile unsigned int *)0x40008018U) /**< \brief (SPI) Interrupt Disable Register */
#define REG_SPI_IMR  (*(  volatile unsigned int *)0x4000801CU) /**< \brief (SPI) Interrupt Mask Register */
#define REG_SPI_CSR  (*(  volatile unsigned int *)0x40008030U) /**< \brief (SPI) Chip Select Register */
#define REG_SPI_WPMR (*(  volatile unsigned int *)0x400080E4U) /**< \brief (SPI) Write Protection Control Register */
#define REG_SPI_WPSR (*(  volatile unsigned int *)0x400080E8U) /**< \brief (SPI) Write Protection Status Register */
#define REG_SPI_RPR  (*(  volatile unsigned int *)0x40008100U) /**< \brief (SPI) Receive Pointer Register */
#define REG_SPI_RCR  (*(  volatile unsigned int *)0x40008104U) /**< \brief (SPI) Receive Counter Register */
#define REG_SPI_TPR  (*(  volatile unsigned int *)0x40008108U) /**< \brief (SPI) Transmit Pointer Register */
#define REG_SPI_TCR  (*(  volatile unsigned int *)0x4000810CU) /**< \brief (SPI) Transmit Counter Register */
#define REG_SPI_RNPR (*(  volatile unsigned int *)0x40008110U) /**< \brief (SPI) Receive Next Pointer Register */
#define REG_SPI_RNCR (*(  volatile unsigned int *)0x40008114U) /**< \brief (SPI) Receive Next Counter Register */
#define REG_SPI_TNPR (*(  volatile unsigned int *)0x40008118U) /**< \brief (SPI) Transmit Next Pointer Register */
#define REG_SPI_TNCR (*(  volatile unsigned int *)0x4000811CU) /**< \brief (SPI) Transmit Next Counter Register */
#define REG_SPI_PTCR (*(  volatile unsigned int *)0x40008120U) /**< \brief (SPI) Transfer Control Register */
#define REG_SPI_PTSR (*(  volatile unsigned int *)0x40008124U) /**< \brief (SPI) Transfer Status Register */

#define SPI_WPMR_WPKEY_PASSWD         (0x535049u << 8) /**< \brief (SPI_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */

//UART

#define REG_UART_CR   (*(  volatile unsigned int *)0x400E0600U) /**< \brief (UART) Control Register */
#define REG_UART_MR   (*(  volatile unsigned int *)0x400E0604U) /**< \brief (UART) Mode Register */
#define REG_UART_IER  (*(  volatile unsigned int *)0x400E0608U) /**< \brief (UART) Interrupt Enable Register */
#define REG_UART_IDR  (*(  volatile unsigned int *)0x400E060CU) /**< \brief (UART) Interrupt Disable Register */
#define REG_UART_IMR  (*(  volatile unsigned int *)0x400E0610U) /**< \brief (UART) Interrupt Mask Register */
#define REG_UART_SR   (*(  volatile unsigned int *)0x400E0614U) /**< \brief (UART) Status Register */
#define REG_UART_RHR  (*(  volatile unsigned int *)0x400E0618U) /**< \brief (UART) Receive Holding Register */
#define REG_UART_THR  (*(  volatile unsigned int *)0x400E061CU) /**< \brief (UART) Transmit Holding Register */
#define REG_UART_BRGR (*(  volatile unsigned int *)0x400E0620U) /**< \brief (UART) Baud Rate Generator Register */



/////////////////////////////////////////////////////////////////////
// PIO Functions
/////////////////////////////////////////////////////////////////////

#define LOW         0 // Value to write a pin low (0 V)
#define HIGH        1 // Value to write a pin high (3.3 V)

#define PORT_ID_A   0 // Arbitrary ID for PIO Port A
#define PORT_ID_B   1 // Arbitrary ID for PIO Port B

#define INPUT       0 // Arbitrary ID for an input I/O line
#define OUTPUT      1 // Arbitrary ID for an output I/O line
#define PERIPH_A    2 // Arbitrary ID for peripheral function A
#define PERIPH_B    3 // Arbitrary ID for peripheral function B
#define PERIPH_C    4 // Arbitrary ID for peripheral function C
#define PERIPH_D    5 // Arbitrary ID for peripheral function D
#define PULL_DOWN   6 // Arbitrary ID for a pull-down resistor
#define FLOATING    7 // Arbitrary ID for neither a pull-up nor a pull-down resistor

// Returns the port ID that corresponds to a given pin
int pinToPort(int pin) {
    return pin >> 5;
}

// Returns a pointer to a Pio-sized chunk of memory at a given port's base address
uint32_t portToBase(int port) {
    return (uint32_t) (port ? PIOB : PIOA);
}

// Given a pin, returns the corresponding port's base address
uint32_t pinToBase(int pin) {
    return portToBase(pinToPort(pin));
}

// Note: Upon reset, pins are configured as input I/O lines (as opposed to being
// controlled by peripheral functions), the peripheral function defaults to PERIPH_A,
// the pull-up resistor is enabled, and the pull-down resistor is disabled. All other
// optional pin functions, which are not provided in this header file, are off upon reset.
void pinMode(int pin, int function) {
    Pio* port = (Pio*) pinToBase(pin);
    int offset = pin % 32;

    switch (function) {
        case INPUT:
            break;
        case OUTPUT:
            port->PIO_OER     |=  (1 << offset); // Configures an I/O line as an output
            break;
        case PERIPH_A:
            port->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            port->PIO_ABCDSR1 &= ~(1 << offset); // Sets the peripheral which controls a pin
            port->PIO_ABCDSR2 &= ~(1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_B:
            port->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            port->PIO_ABCDSR1 |=  (1 << offset); // Sets the peripheral which controls a pin
            port->PIO_ABCDSR2 &= ~(1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_C:
            port->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            port->PIO_ABCDSR1 &= ~(1 << offset); // Sets the peripheral which controls a pin
            port->PIO_ABCDSR2 |=  (1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_D:
            port->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            port->PIO_ABCDSR1 |=  (1 << offset); // Sets the peripheral which controls a pin
            port->PIO_ABCDSR2 |=  (1 << offset); // Sets the peripheral which controls a pin
            break;
        case PULL_DOWN:
            port->PIO_PUDR    |=  (1 << offset); // Disables the pull-up resistor
            port->PIO_PPDER   |=  (1 << offset); // Enables the pull-down resistor
        case FLOATING:
            port->PIO_PUDR    |=  (1 << offset); // Disables the pull-down resistor
    }
}

// Reads the digital voltage on a pin configured as an input I/O line
int digitalRead(int pin) {
    Pio* port = (Pio*) pinToBase(pin);
    int offset = pin % 32;
    return ((port->PIO_PDSR) >> offset) & 1;
}

// Writes a digital voltage to a pin configured as an output I/O line
void digitalWrite(int pin, int val) {
    Pio* port = (Pio*) pinToBase(pin);
    int offset = pin % 32;
    if (val) {
        port->PIO_SODR |= (1 << offset);
    } else {
        port->PIO_CODR |= (1 << offset);
    }
}

// Switches the digital voltage on a pin configured as in output I/O line
void toggle(int pin) {
    int currentVal = digitalRead(pin);
    digitalWrite(pin, !currentVal);
}


/////////////////////////////////////////////////////////////////////
// TC Functions
/////////////////////////////////////////////////////////////////////

#define TIMER_CLOCK1_SPEED (MCK / 2)
#define TIMER_CLOCK2_SPEED (MCK / 8)
#define TIMER_CLOCK3_SPEED (MCK / 32)
#define TIMER_CLOCK4_SPEED (MCK / 128)
#define TIMER_CLOCK5_SPEED (MCK) // Change this

#define TIMER_CLOCK1_ID    0
#define TIMER_CLOCK2_ID    1
#define TIMER_CLOCK3_ID    2
#define TIMER_CLOCK4_ID    3
#define TIMER_CLOCK5_ID    4

#define TC_BLOCK0_ID       0
#define TC_BLOCK1_ID       1

#define TC_CH0_ID          0
#define TC_CH1_ID          1
#define TC_CH2_ID          2
#define TC_CH3_ID          3
#define TC_CH4_ID          4
#define TC_CH5_ID          5

#define TC_CHANNEL_OFFSET  (0x40U)

#define UP                 0
#define UPDOWN             1
#define UP_RC              2
#define UPDOWN_RC          3


// Returns the TC block ID that corresponds to a given channel
int channelToBlock(int channelID) {
    return channelID / 3;
}

// Returns a pointer to a Tc-sized chunk of memory at a given block's base address
uint32_t blockToBlockBase(int block) {
    uint32_t base = block ? TC1 : TC0;
}

uint32_t channelToBlockBase(int channelID) {
    return blockToBlockBase(channelToBlock(channelID));
}

uint32_t channelToChannelBase(int channelID) {
    uint32_t base = channelToBlockBase(channelID);
    uint32_t offset = (channelID % 3) * TC_CHANNEL_OFFSET;
    return base + offset;
}

void channelInit(int channelID, int clock, int mode) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    channel->TC_CCR.CLKEN   = 1;     // Enable clock
    channel->TC_CMR.TCCLKS  = clock; // Set clock to desired clock
    channel->TC_CMR.WAVE    = 1;     // Waveform mode
    channel->TC_CMR.WAVESEL = mode;  // Set counting mdoe to desired mode
}

uint32_t readChannel(int channelID) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    return channel->TC_CV;
}

void resetChannel(int channelID) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    channel->TC_CCR.SWTRG = 1;
}

void setRC_compare(int channelID, uint32_t val) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    channel->TC_RC = val;
}

int checkRC_Compare(int channelID) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    return channel->TC_SR.CPCS;
}

// Configure TC Channel 0 to perform delays
void delayInit() {
    channelInit(TC_CH0_ID, TIMER_CLOCK1_ID, UP_RC);
}

// Works up to (2^15 - 1 = 32767) us
// TIMER_CLOCK1 has a resolution of 0.5 us
void delayMicros(uint32_t duration) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(TC_CH0_ID);
    channel->TC_CCR.SWTRG = 1; // Reset counter
    channel->TC_RC = duration * (TIMER_CLOCK1_SPEED / 1e6); // Set compare value
    while(!(channel->TC_SR.CPCS)); // Wait until an RC Compare has occurred
}

// Uses delayMicros(), at Prof. Harris's request
void delayMillis(int duration) {
    for (int i = 0; i < duration; i++) {
        delayMicros(1000);
    }
}

// Uses Millis(), at Prof. Harris's request
void delaySeconds(int duration) {
    for (int i = 0; i < duration; i++) {
        delayMillis(1000);
    }
}


/*----------------------------
--------SPI METHODS-------------
----------------------------*/

void spiInit(char clkdivide, int cpol, int ncpha) {
    /*Initializes the SPI interface for Chip Select line 0

    clkdivide (0x01 to 0xFF). The SPI clk will be the master clock / clkdivide
    cpol: clock polarity (0: inactive state is logic level 0, 1: inactive state is logic level 1)
    ncpha: clock phase (0: data changed on leading edge of clk and captured on next edge, 1: data captured on leading edge of clk and changed on next edge)
    Please see p585-p586 for cpol/ncpha timing diagrams

    This implements only: (p601/p610)
        1) SPI Master Mode
        2) Fixed Peripheral Select
        3) Mode Fault Detection Enabled
        4) Local Loopback Disabled
        5) 8 Bits Per Transfer
    Please read the SPI User Interface section of the datasheet for more advanced configuration features
    */

   //Initially assigning SPI pins (PA11-PA14) to peripheral A (SPI). Pin mapping given in p38-p39
    pinMode(11, PERIPH_A);
    pinMode(12, PERIPH_A);
    pinMode(13, PERIPH_A);
    pinMode(14, PERIPH_A);

    //next setting the SPI control register (p600). Set to 1 to enable SPI
    REG_SPI_CR = 1;

    //next setting the SPI mode register (p601) with the following:
		//master mode
		//fixed peripheral select
		//chip select lines directly connected to peripheral device
		//mode fault detection enabled
		//WDRBT disabled
		//LLB disabled
		//PCS = 0000 (Peripheral 0 selected), means NPCS[3:0] = 1110
		REG_SPI_MR = 1;

    //next setting the chip select register for peripheral 0 (p610)
    //ignoring delays
		
    //REG_SPI_CSR = (cpol<<0) | (ncpha<<1) | (clkdivide << 16);
		REG_SPI_CSR = 0x0000FF00;
}

char spiSendReceive(char send) {
    //Sends one byte over SPI and returns the received character
    REG_SPI_TDR = send;
    //Wait until Receive Data Register Full (RDRF, bit 0) and TXEMPTY (bit )
    while ( !( (REG_SPI_SR & 1) & ((REG_SPI_SR >> 9) & 1) ) );
    //After these status bits have gone high, the transaction is complete  
    return REG_SPI_RDR;
}

short spiSendReceive16(short send) {
    //sends one 16-bit short over SPI and returns the received short
    short rec;
    rec = spiSendReceive((send & 0xFF00) >> 8); // send data MSB first
    rec = (rec << 8) | spiSendReceive(send & 0xFF);
    return rec;
}


/*----------------------------
--------UART METHODS-------------
----------------------------*/

/* Initialize UART. Note that pin PA9 is used as receive and pin PA10 
 * is used as transmit. samInit() must be called first.
 * parity:
 *	 0: Even
 *	 1: Odd
 *	 2: Space (forced to 0)
 *	 3: Mark (forced to 1)
 *	 4: No (no parity)
 * Baud Rate =  MCK/(16*CD), CD is an unsigned short
 */	
void uartInit(int parity, int CD) {
	pinMode(9, PERIPH_A);		  // Set URXD0 pin mode
	pinMode(10, PERIPH_A);		  // Set ITXD0 pin mode

	REG_UART_CR   |= 1 << 6; // Enable transmitter
	REG_UART_CR   |= 1 << 4; // Enable receiver
	
	// Parity
	//REG_UART_MR   |= parity << 9;    
	//REG_UART_MR   &= ~(parity << 9);
	REG_UART_MR   |= 1 << 11;
	REG_UART_MR   &= ~((0x3) << 9);
	
	REG_UART_BRGR = CD;	  // Set baud rate divider
}

// Transmits a character (1 byte) over UART
void uartTx(char data) {
	while (!((REG_UART_SR >> 1) & 1)); // Wait until previous data has been transmitted
	REG_UART_THR = data; // Write data into holding register for transmit
}

// Returns a character (1 byte) received over UART
char uartRx() {
	while(!((REG_UART_SR) & 1)); // Wait until data has been received
	return (char) REG_UART_RHR; // Return received data in holding register
	
}

/////////////////////////////////////////////////////////////////////
// General Functions
/////////////////////////////////////////////////////////////////////
void samInit() {
    //Many peripherals on the SAM4S are write protected: unless the correct password is written in a peripheral memory address, write access to peripheral control registers is disabled. This is done for security reasons, but is not necessary in this header file. In the first part of this function, we enable write access to the PMC, PIO, SPI, and UART by writing a password into the peripheral's Write Protect Mode Register (WPMR)

	//disabling PMC write protection (Password: "PMC")
    *((uint32_t *) REG_PMC_WPMR) = PMC_WPMR_WPKEY_PASSWD;
	//disabling PIO write protection (Password: "PIO")
    Pio* pioBaseA = (Pio*) PIOA;
    Pio* pioBaseB = (Pio*) PIOB;
    pioBaseA->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
    pioBaseB->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//disabling SPI write protection (Password: "SPI")
    *((uint32_t *) REG_SPI_WPMR) = SPI_WPMR_WPKEY_PASSWD;
	//There is no UART write protection

	//disabling timer write protection (Password: "TIM")
    Tc* tcBase0 = (Tc*) TC0;
    Tc* tcBase1 = (Tc*) TC1;
    tcBase0->TC_WPMR = TC_WPMR_WPKEY_PASSWD;
    tcBase1->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

    //We next need to supply a clock to these peripherals. For a given peripheral, clock is enabled by writing a 1 into a specific bit of the PMC Peripheral Clock Enable Register (PCER). There are two registers for the 34 peripherals. Peripheral - bit number mapping is given in p36: Peripheral Identifiers.

    //Activating clocks for UART 0 (PID 8), PIO A (PID 11), SPI (PID 21), TC0 (Timer/Counter CH0) (PID 23)

	*((uint32_t *) REG_PMC_PCER0) |= (1<<8);
	*((uint32_t *) REG_PMC_PCER0) |= (1<<11);
	*((uint32_t *) REG_PMC_PCER0) |= (1<<21);
	*((uint32_t *) REG_PMC_PCER0) |= (1<<23);
}

#endif
