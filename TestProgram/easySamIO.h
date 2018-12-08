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
 * PIO:   Bit field pass                    DONE
 * TIMER: Add support for TC1               DONE
 * TIMER: Refine delays, add delay_us()     DONE
 * TIMER: Add slow clock functionality      NOT STARTED
 * TIMER: Bit field pass                    DONE
 * PMC:   Add support for FPGA clock        NOT STARTED
 * PMC:   Bit fields                        DONE
 * SPI:   Fix "PCK" issue                   DONE
 * SPI:   Bit field pass                    DONE
 * UART:  Bit field pass                    DONE
 * PWM:   Add base support                  NOT STARTED
 * PWM:   Test                              NOT STARTED
 * PWM:   Bit field pass                    NOT STARTED
 * ADC:   Add base support                  NOT STARTED
 * ADC:   Test                              NOT STARTED
 * ADC:   Bit field pass                    NOT STARTED
 * RTC:   Add base support                  NOT STARTED
 * RTC:   Bit field pass                    NOT STARTED
 * All:   Improve WPMR Keys?                NOT STARTED
 * All:   Final pass                        NOT STARTED
 */

//Constants taken from ATSAM4S4B CMSIS Library
//Relevant code is available at http://packs.download.atmel.com/

#ifndef EASY_SAM_IO_H
#define EASY_SAM_IO_H

#include <stdint.h>


/////////////////////////////////////////////////////////////////////
// Top-Level Constants
/////////////////////////////////////////////////////////////////////

#define MCK   4000000


/////////////////////////////////////////////////////////////////////
// Base Address Definitions
/////////////////////////////////////////////////////////////////////

#define SPI   (0x40008000U) /**< \brief SPI Base Address */
#define TC0   (0x40010000U) /**< \brief TC0 Base Address */
#define TC1   (0x40014000U) /**< \brief TC1 Base Address */
#define PWM   (0x40020000U) /**< \brief PWM Base Address */
#define ADC   (0x40038000U) /**< \brief ADC Base Address */
#define PMC   (0x400E0400U) /**< \brief PMC Base Address */
#define UART0 (0x400E0600U) /**< \brief UART0 Base Address */
#define PIOA  (0x400E0E00U) /**< \brief PIOA Base Address */
#define PIOB  (0x400E1000U) /**< \brief PIOB Base Address */
#define RTC   (0x400E1460U) /**< \brief RTC Base Address */


/////////////////////////////////////////////////////////////////////
// PMC (Power Management Controller) Registers
/////////////////////////////////////////////////////////////////////

/** \brief Pmc hardware registers */
typedef struct {
    volatile uint32_t PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
    volatile uint32_t PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
    volatile uint32_t PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
    volatile uint32_t Reserved1[1];
    volatile uint32_t PMC_PCER0;     /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register 0 */
    volatile uint32_t PMC_PCDR0;     /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register 0 */
    volatile uint32_t PMC_PCSR0;     /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register 0 */
    volatile uint32_t Reserved2[1];
    volatile uint32_t CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
    volatile uint32_t CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
    volatile uint32_t CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
    volatile uint32_t CKGR_PLLBR;    /**< \brief (Pmc Offset: 0x002C) PLLB Register */
    volatile uint32_t PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
    volatile uint32_t Reserved3[1];
    volatile uint32_t PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
    volatile uint32_t Reserved4[1];
    volatile uint32_t PMC_PCK[3];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
    volatile uint32_t Reserved5[5];
    volatile uint32_t PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
    volatile uint32_t PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
    volatile uint32_t PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
    volatile uint32_t PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
    volatile uint32_t PMC_FSMR;      /**< \brief (Pmc Offset: 0x0070) Fast Startup Mode Register */
    volatile uint32_t PMC_FSPR;      /**< \brief (Pmc Offset: 0x0074) Fast Startup Polarity Register */
    volatile uint32_t PMC_FOCR;      /**< \brief (Pmc Offset: 0x0078) Fault Output Clear Register */
    volatile uint32_t Reserved6[26];
    volatile uint32_t PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
    volatile uint32_t PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
    volatile uint32_t Reserved7[5];
    volatile uint32_t PMC_PCER1;     /**< \brief (Pmc Offset: 0x0100) Peripheral Clock Enable Register 1 */
    volatile uint32_t PMC_PCDR1;     /**< \brief (Pmc Offset: 0x0104) Peripheral Clock Disable Register 1 */
    volatile uint32_t PMC_PCSR1;     /**< \brief (Pmc Offset: 0x0108) Peripheral Clock Status Register 1 */
    volatile uint32_t Reserved8[1];
    volatile uint32_t PMC_OCR;       /**< \brief (Pmc Offset: 0x0110) Oscillator Calibration Register */
} Pmc;

#define PMC_REGS ((Pmc *) PMC)

#define ID_SUPC   ( 0) /**< \brief Supply Controller (SUPC) */
#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) */
#define ID_RTC    ( 2) /**< \brief Real Time Clock (RTC) */
#define ID_RTT    ( 3) /**< \brief Real Time Timer (RTT) */
#define ID_WDT    ( 4) /**< \brief Watchdog Timer (WDT) */
#define ID_PMC    ( 5) /**< \brief Power Management Controller (PMC) */
#define ID_EFC    ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) */
#define ID_UART0  ( 8) /**< \brief UART 0 (UART0) */
#define ID_UART1  ( 9) /**< \brief UART 1 (UART1) */
#define ID_PIOA   (11) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB   (12) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_USART0 (14) /**< \brief USART 0 (USART0) */
#define ID_USART1 (15) /**< \brief USART 1 (USART1) */
#define ID_HSMCI  (18) /**< \brief Multimedia Card Interface (HSMCI) */
#define ID_TWI0   (19) /**< \brief Two Wire Interface 0 (TWI0) */
#define ID_TWI1   (20) /**< \brief Two Wire Interface 1 (TWI1) */
#define ID_SPI    (21) /**< \brief Serial Peripheral Interface (SPI) */
#define ID_SSC    (22) /**< \brief Synchronous Serial Controler (SSC) */
#define ID_TC0    (23) /**< \brief Timer/Counter 0 (TC0) */
#define ID_TC1    (24) /**< \brief Timer/Counter 1 (TC1) */
#define ID_TC2    (25) /**< \brief Timer/Counter 2 (TC2) */
#define ID_ADC    (29) /**< \brief Analog To Digital Converter (ADC) */
#define ID_DACC   (30) /**< \brief Digital To Analog Converter (DACC) */
#define ID_PWM    (31) /**< \brief Pulse Width Modulation (PWM) */
#define ID_CRCCU  (32) /**< \brief CRC Calculation Unit (CRCCU) */
#define ID_ACC    (33) /**< \brief Analog Comparator (ACC) */
#define ID_UDP    (34) /**< \brief USB Device Port (UDP) */

#define PMC_WPMR_WPKEY_PASSWD           (0x504D43U << 8) /**< \brief (PMC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// PIO (Parallel Input/Output) Registers
/////////////////////////////////////////////////////////////////////

typedef struct {
    volatile uint32_t PIO_PER;        /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
    volatile uint32_t PIO_PDR;        /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
    volatile uint32_t PIO_PSR;        /**< \brief (Pio Offset: 0x0008) PIO Status Register */
    volatile uint32_t Reserved1[1];
    volatile uint32_t PIO_OER;        /**< \brief (Pio Offset: 0x0010) Output Enable Register */
    volatile uint32_t PIO_ODR;        /**< \brief (Pio Offset: 0x0014) Output Disable Register */
    volatile uint32_t PIO_OSR;        /**< \brief (Pio Offset: 0x0018) Output Status Register */
    volatile uint32_t Reserved2[1];
    volatile uint32_t PIO_IFER;       /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
    volatile uint32_t PIO_IFDR;       /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
    volatile uint32_t PIO_IFSR;       /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
    volatile uint32_t Reserved3[1];
    volatile uint32_t PIO_SODR;       /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
    volatile uint32_t PIO_CODR;       /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
    volatile uint32_t PIO_ODSR;       /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
    volatile uint32_t PIO_PDSR;       /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
    volatile uint32_t PIO_IER;        /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
    volatile uint32_t PIO_IDR;        /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
    volatile uint32_t PIO_IMR;        /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
    volatile uint32_t PIO_ISR;        /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
    volatile uint32_t PIO_MDER;       /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
    volatile uint32_t PIO_MDDR;       /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
    volatile uint32_t PIO_MDSR;       /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
    volatile uint32_t Reserved4[1];
    volatile uint32_t PIO_PUDR;       /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
    volatile uint32_t PIO_PUER;       /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
    volatile uint32_t PIO_PUSR;       /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
    volatile uint32_t Reserved5[1];
    volatile uint32_t PIO_ABCDSR1;  /**< \brief (Pio Offset: 0x0070) Peripheral Select Register 1 */
    volatile uint32_t PIO_ABCDSR2;  /**< \brief (Pio Offset: 0x0074) Peripheral Select Register 2 */
    volatile uint32_t Reserved6[2];
    volatile uint32_t PIO_IFSCDR;     /**< \brief (Pio Offset: 0x0080) Input Filter Slow Clock Disable Register */
    volatile uint32_t PIO_IFSCER;     /**< \brief (Pio Offset: 0x0084) Input Filter Slow Clock Enable Register */
    volatile uint32_t PIO_IFSCSR;     /**< \brief (Pio Offset: 0x0088) Input Filter Slow Clock Status Register */
    volatile uint32_t PIO_SCDR;       /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
    volatile uint32_t PIO_PPDDR;      /**< \brief (Pio Offset: 0x0090) Pad Pull-down Disable Register */
    volatile uint32_t PIO_PPDER;      /**< \brief (Pio Offset: 0x0094) Pad Pull-down Enable Register */
    volatile uint32_t PIO_PPDSR;      /**< \brief (Pio Offset: 0x0098) Pad Pull-down Status Register */
    volatile uint32_t Reserved7[1];
    volatile uint32_t PIO_OWER;       /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
    volatile uint32_t PIO_OWDR;       /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
    volatile uint32_t PIO_OWSR;       /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
    volatile uint32_t Reserved8[1];
    volatile uint32_t PIO_AIMER;      /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
    volatile uint32_t PIO_AIMDR;      /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
    volatile uint32_t PIO_AIMMR;      /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
    volatile uint32_t Reserved9[1];
    volatile uint32_t PIO_ESR;        /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
    volatile uint32_t PIO_LSR;        /**< \brief (Pio Offset: 0x00C4) Level Select Register */
    volatile uint32_t PIO_ELSR;       /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
    volatile uint32_t Reserved10[1];
    volatile uint32_t PIO_FELLSR;     /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
    volatile uint32_t PIO_REHLSR;     /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
    volatile uint32_t PIO_FRLHSR;     /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
    volatile uint32_t Reserved11[1];
    volatile uint32_t PIO_LOCKSR;     /**< \brief (Pio Offset: 0x00E0) Lock Status */
    volatile uint32_t PIO_WPMR;       /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
    volatile uint32_t PIO_WPSR;       /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
    volatile uint32_t Reserved12[5];
    volatile uint32_t PIO_SCHMITT;    /**< \brief (Pio Offset: 0x0100) Schmitt Trigger Register */
    volatile uint32_t Reserved13[19];
    volatile uint32_t PIO_PCMR;       /**< \brief (Pio Offset: 0x150) Parallel Capture Mode Register */
    volatile uint32_t PIO_PCIER;      /**< \brief (Pio Offset: 0x154) Parallel Capture Interrupt Enable Register */
    volatile uint32_t PIO_PCIDR;      /**< \brief (Pio Offset: 0x158) Parallel Capture Interrupt Disable Register */
    volatile uint32_t PIO_PCIMR;      /**< \brief (Pio Offset: 0x15C) Parallel Capture Interrupt Mask Register */
    volatile uint32_t PIO_PCISR;      /**< \brief (Pio Offset: 0x160) Parallel Capture Interrupt Status Register */
    volatile uint32_t PIO_PCRHR;      /**< \brief (Pio Offset: 0x164) Parallel Capture Reception Holding Register */
    volatile uint32_t PIO_RPR;        /**< \brief (Pio Offset: 0x168) Receive Pointer Register */
    volatile uint32_t PIO_RCR;        /**< \brief (Pio Offset: 0x16C) Receive Counter Register */
    volatile uint32_t Reserved14[2];
    volatile uint32_t PIO_RNPR;       /**< \brief (Pio Offset: 0x178) Receive Next Pointer Register */
    volatile uint32_t PIO_RNCR;       /**< \brief (Pio Offset: 0x17C) Receive Next Counter Register */
    volatile uint32_t Reserved15[2];
    volatile uint32_t PIO_PTCR;       /**< \brief (Pio Offset: 0x188) Transfer Control Register */
    volatile uint32_t PIO_PTSR;       /**< \brief (Pio Offset: 0x18C) Transfer Status Register */
} Pio;

#define PIOA_REGS ((Pio*) PIOA)
#define PIOB_REGS ((Pio*) PIOB)

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

#define PIO_WPMR_WPKEY_PASSWD (0x50494Fu << 8) /**< \brief (PIO_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// TC (Timer Counter) Registers
/////////////////////////////////////////////////////////////////////

typedef struct {
    volatile uint32_t CLKEN   : 1;
    volatile uint32_t CLKDIS  : 1;
    volatile uint32_t SWTRG   : 1;
    volatile uint32_t         : 29;
} TC_CCR_bits;

typedef struct {
    volatile uint32_t TCCLKS  : 3;
    volatile uint32_t CLKI    : 1;
    volatile uint32_t BURST   : 2;
    volatile uint32_t CPCSTOP : 1;
    volatile uint32_t CPCDIS  : 1;
    volatile uint32_t EEVTEDG : 2;
    volatile uint32_t EEVT    : 2;
    volatile uint32_t ENETRG  : 1;
    volatile uint32_t WAVESEL : 2;
    volatile uint32_t WAVE    : 1;
    volatile uint32_t ACPA    : 2;
    volatile uint32_t ACPC    : 2;
    volatile uint32_t AEEVT   : 2;
    volatile uint32_t ASWTRG  : 2;
    volatile uint32_t BCPB    : 2;
    volatile uint32_t BCPC    : 2;
    volatile uint32_t BEEVT   : 2;
    volatile uint32_t BSWTRG  : 2;
} TC_CMR_bits;

typedef struct {
    volatile uint32_t COVFS   : 1;
    volatile uint32_t LOVRS   : 1;
    volatile uint32_t CPAS    : 1;
    volatile uint32_t CPBS    : 1;
    volatile uint32_t CPCS    : 1;
    volatile uint32_t LDRAS   : 1;
    volatile uint32_t LDRBS   : 1;
    volatile uint32_t ETRGS   : 1;
    volatile uint32_t         : 8;
    volatile uint32_t CLKSTA  : 1;
    volatile uint32_t MTIOA   : 1;
    volatile uint32_t MTIOB   : 1;
    volatile uint32_t         : 13;
} TC_SR_bits;

/** \brief TcChannel hardware registers */
typedef struct {
    volatile TC_CCR_bits TC_CCR;        /**< \brief (TcChannel Offset: 0x0) Channel Control Register */
    volatile TC_CMR_bits TC_CMR;        /**< \brief (TcChannel Offset: 0x4) Channel Mode Register */
    volatile uint32_t    TC_SMMR;       /**< \brief (TcChannel Offset: 0x8) Stepper Motor Mode Register */
    volatile uint32_t    Reserved1[1];
    volatile uint32_t    TC_CV;         /**< \brief (TcChannel Offset: 0x10) Counter Value */
    volatile uint32_t    TC_RA;         /**< \brief (TcChannel Offset: 0x14) Register A */
    volatile uint32_t    TC_RB;         /**< \brief (TcChannel Offset: 0x18) Register B */
    volatile uint32_t    TC_RC;         /**< \brief (TcChannel Offset: 0x1C) Register C */
    volatile TC_SR_bits  TC_SR;         /**< \brief (TcChannel Offset: 0x20) Status Register */
    volatile uint32_t    TC_IER;        /**< \brief (TcChannel Offset: 0x24) Interrupt Enable Register */
    volatile uint32_t    TC_IDR;        /**< \brief (TcChannel Offset: 0x28) Interrupt Disable Register */
    volatile uint32_t    TC_IMR;        /**< \brief (TcChannel Offset: 0x2C) Interrupt Mask Register */
    volatile uint32_t    Reserved2[4];
} TcChannel;

/** \brief Tc hardware registers */
#define TCCHANNEL_NUMBER 3
typedef struct {
    TcChannel         TC_CHANNEL[TCCHANNEL_NUMBER]; /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */
    volatile uint32_t TC_BCR;        /**< \brief (Tc Offset: 0xC0) Block Control Register */
    volatile uint32_t TC_BMR;        /**< \brief (Tc Offset: 0xC4) Block Mode Register */
    volatile uint32_t TC_QIER;       /**< \brief (Tc Offset: 0xC8) QDEC Interrupt Enable Register */
    volatile uint32_t TC_QIDR;       /**< \brief (Tc Offset: 0xCC) QDEC Interrupt Disable Register */
    volatile uint32_t TC_QIMR;       /**< \brief (Tc Offset: 0xD0) QDEC Interrupt Mask Register */
    volatile uint32_t TC_QISR;       /**< \brief (Tc Offset: 0xD4) QDEC Interrupt Status Register */
    volatile uint32_t TC_FMR;        /**< \brief (Tc Offset: 0xD8) Fault Mode Register */
    volatile uint32_t Reserved1[2];
    volatile uint32_t TC_WPMR;       /**< \brief (Tc Offset: 0xE4) Write Protect Mode Register */
} Tc;

#define TC0_REGS ((Tc*) TC0)
#define TC1_REGS ((Tc*) TC1)

#define TC_WPMR_WPKEY_PASSWD (0x54494Du << 8) /**< \brief (TC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// SPI (Serial Peripheral Interface) Registers
/////////////////////////////////////////////////////////////////////

typedef struct {
    volatile uint32_t SPIEN    : 1;
    volatile uint32_t SPIDIS   : 1;
    volatile uint32_t          : 5;
    volatile uint32_t SWRST    : 1;
    volatile uint32_t          : 16;
    volatile uint32_t LASTXFER : 1;
    volatile uint32_t          : 7;
} SPI_CR_bits;

typedef struct {
    volatile uint32_t MSTR    : 1;
    volatile uint32_t PS      : 1;
    volatile uint32_t PCSDEC  : 1;
    volatile uint32_t         : 1;
    volatile uint32_t MODFDIS : 1;
    volatile uint32_t WDRBT   : 1;
    volatile uint32_t         : 1;
    volatile uint32_t LLB     : 1;
    volatile uint32_t         : 8;
    volatile uint32_t PCS     : 4;
    volatile uint32_t         : 4;
    volatile uint32_t DLYBCS  : 8;
} SPI_MR_bits;

typedef struct {
    volatile uint32_t RD  : 16;
    volatile uint32_t PCS : 4;
    volatile uint32_t     : 12;
} SPI_RDR_bits;

typedef struct {
    volatile uint32_t TD       : 16;
    volatile uint32_t PCS      : 4;
    volatile uint32_t          : 4;
    volatile uint32_t LASTXFER : 1;
    volatile uint32_t          : 7;
} SPI_TDR_bits;

typedef struct {
    volatile uint32_t RDRF    : 1;
    volatile uint32_t TDRE    : 1;
    volatile uint32_t MODF    : 1;
    volatile uint32_t OVRES   : 1;
    volatile uint32_t ENDRX   : 1;
    volatile uint32_t ENDTX   : 1;
    volatile uint32_t RXBUFF  : 1;
    volatile uint32_t TXBUFE  : 1;
    volatile uint32_t NSSR    : 1;
    volatile uint32_t TXEMPTY : 1;
    volatile uint32_t UNDES   : 1;
    volatile uint32_t         : 5;
    volatile uint32_t SPIENS  : 1;
    volatile uint32_t         : 15;
} SPI_SR_bits;

typedef struct {
    volatile uint32_t CPOL   : 1;
    volatile uint32_t NCPHA  : 1;
    volatile uint32_t CSNAAT : 1;
    volatile uint32_t CSAAT  : 1;
    volatile uint32_t BITS   : 4;
    volatile uint32_t SCBR   : 8;
    volatile uint32_t DLYBS  : 8;
    volatile uint32_t DLYBCT : 8;
} SPI_CSR_bits;

/** \brief Spi hardware registers */
typedef struct {
    volatile SPI_CR_bits  SPI_CR;        /**< \brief (Spi Offset: 0x00) Control Register */
    volatile SPI_MR_bits  SPI_MR;        /**< \brief (Spi Offset: 0x04) Mode Register */
    volatile SPI_RDR_bits SPI_RDR;       /**< \brief (Spi Offset: 0x08) Receive Data Register */
    volatile SPI_TDR_bits SPI_TDR;       /**< \brief (Spi Offset: 0x0C) Transmit Data Register */
    volatile SPI_SR_bits  SPI_SR;        /**< \brief (Spi Offset: 0x10) Status Register */
    volatile uint32_t     SPI_IER;       /**< \brief (Spi Offset: 0x14) Interrupt Enable Register */
    volatile uint32_t     SPI_IDR;       /**< \brief (Spi Offset: 0x18) Interrupt Disable Register */
    volatile uint32_t     SPI_IMR;       /**< \brief (Spi Offset: 0x1C) Interrupt Mask Register */
    volatile uint32_t     Reserved1[4];
    volatile SPI_CSR_bits SPI_CSR0;    /**< \brief (Spi Offset: 0x30) Chip Select Register 0 */
    volatile SPI_CSR_bits SPI_CSR1;    /**< \brief (Spi Offset: 0x30) Chip Select Register 1 */
    volatile SPI_CSR_bits SPI_CSR2;    /**< \brief (Spi Offset: 0x30) Chip Select Register 2 */
    volatile SPI_CSR_bits SPI_CSR3;    /**< \brief (Spi Offset: 0x30) Chip Select Register 3 */
    volatile uint32_t     Reserved2[41];
    volatile uint32_t     SPI_WPMR;      /**< \brief (Spi Offset: 0xE4) Write Protection Control Register */
    volatile uint32_t     SPI_WPSR;      /**< \brief (Spi Offset: 0xE8) Write Protection Status Register */
    volatile uint32_t     Reserved3[5];
    volatile uint32_t     SPI_RPR;       /**< \brief (Spi Offset: 0x100) Receive Pointer Register */
    volatile uint32_t     SPI_RCR;       /**< \brief (Spi Offset: 0x104) Receive Counter Register */
    volatile uint32_t     SPI_TPR;       /**< \brief (Spi Offset: 0x108) Transmit Pointer Register */
    volatile uint32_t     SPI_TCR;       /**< \brief (Spi Offset: 0x10C) Transmit Counter Register */
    volatile uint32_t     SPI_RNPR;      /**< \brief (Spi Offset: 0x110) Receive Next Pointer Register */
    volatile uint32_t     SPI_RNCR;      /**< \brief (Spi Offset: 0x114) Receive Next Counter Register */
    volatile uint32_t     SPI_TNPR;      /**< \brief (Spi Offset: 0x118) Transmit Next Pointer Register */
    volatile uint32_t     SPI_TNCR;      /**< \brief (Spi Offset: 0x11C) Transmit Next Counter Register */
    volatile uint32_t     SPI_PTCR;      /**< \brief (Spi Offset: 0x120) Transfer Control Register */
    volatile uint32_t     SPI_PTSR;      /**< \brief (Spi Offset: 0x124) Transfer Status Register */
} Spi;

#define SPI_REGS ((Spi*) SPI)

#define SPI_WPMR_WPKEY_PASSWD         (0x535049u << 8) /**< \brief (SPI_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */


/////////////////////////////////////////////////////////////////////
// UART (Universal Asynchronous Receiver-Transmitter) Registers
/////////////////////////////////////////////////////////////////////

typedef struct {
    volatile uint32_t        : 2;
    volatile uint32_t RSTRX  : 1;
    volatile uint32_t RSTTX  : 1;
    volatile uint32_t RXEN   : 1;
    volatile uint32_t RXDIS  : 1;
    volatile uint32_t TXEN   : 1;
    volatile uint32_t TXDIS  : 1;
    volatile uint32_t RSTSTA : 1;
    volatile uint32_t        : 23;
} UART_CR_bits;

typedef struct {
    volatile uint32_t        : 9;
    volatile uint32_t PAR    : 3;
    volatile uint32_t        : 2;
    volatile uint32_t CHMODE : 2;
    volatile uint32_t        : 16;
} UART_MR_bits;

typedef struct {
    volatile uint32_t RXRDY   : 1;
    volatile uint32_t TXRDY   : 1;
    volatile uint32_t         : 1;
    volatile uint32_t ENDRX   : 1;
    volatile uint32_t ENDTX   : 1;
    volatile uint32_t OVRE    : 1;
    volatile uint32_t FRAME   : 1;
    volatile uint32_t PARE    : 1;
    volatile uint32_t         : 1;
    volatile uint32_t TXEMPTY : 1;
    volatile uint32_t         : 1;
    volatile uint32_t TXBUFE  : 1;
    volatile uint32_t RXBUFE  : 1;
    volatile uint32_t         : 19;
} UART_SR_bits;

/** \brief Uart hardware registers */
typedef struct {
    volatile UART_CR_bits UART_CR;       /**< \brief (Uart Offset: 0x0000) Control Register */
    volatile UART_MR_bits UART_MR;       /**< \brief (Uart Offset: 0x0004) Mode Register */
    volatile uint32_t     UART_IER;      /**< \brief (Uart Offset: 0x0008) Interrupt Enable Register */
    volatile uint32_t     UART_IDR;      /**< \brief (Uart Offset: 0x000C) Interrupt Disable Register */
    volatile uint32_t     UART_IMR;      /**< \brief (Uart Offset: 0x0010) Interrupt Mask Register */
    volatile UART_SR_bits UART_SR;       /**< \brief (Uart Offset: 0x0014) Status Register */
    volatile uint32_t     UART_RHR;      /**< \brief (Uart Offset: 0x0018) Receive Holding Register */
    volatile uint32_t     UART_THR;      /**< \brief (Uart Offset: 0x001C) Transmit Holding Register */
    volatile uint32_t     UART_BRGR;     /**< \brief (Uart Offset: 0x0020) Baud Rate Generator Register */
    volatile uint32_t     Reserved1[55];
    volatile uint32_t     UART_RPR;      /**< \brief (Uart Offset: 0x100) Receive Pointer Register */
    volatile uint32_t     UART_RCR;      /**< \brief (Uart Offset: 0x104) Receive Counter Register */
    volatile uint32_t     UART_TPR;      /**< \brief (Uart Offset: 0x108) Transmit Pointer Register */
    volatile uint32_t     UART_TCR;      /**< \brief (Uart Offset: 0x10C) Transmit Counter Register */
    volatile uint32_t     UART_RNPR;     /**< \brief (Uart Offset: 0x110) Receive Next Pointer Register */
    volatile uint32_t     UART_RNCR;     /**< \brief (Uart Offset: 0x114) Receive Next Counter Register */
    volatile uint32_t     UART_TNPR;     /**< \brief (Uart Offset: 0x118) Transmit Next Pointer Register */
    volatile uint32_t     UART_TNCR;     /**< \brief (Uart Offset: 0x11C) Transmit Next Counter Register */
    volatile uint32_t     UART_PTCR;     /**< \brief (Uart Offset: 0x120) Transfer Control Register */
    volatile uint32_t     UART_PTSR;     /**< \brief (Uart Offset: 0x124) Transfer Status Register */
} Uart;

#define UART_REGS ((Uart*) UART0)


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

// Returns the given port's base address
uint32_t portToBase(int port) {
    return (uint32_t) (port ? PIOB : PIOA);
}

// Given a pin, returns the corresponding port's base address
uint32_t pinToBase(int pin) {
    return portToBase(pinToPort(pin));
}

/* Note: Upon reset, pins are configured as input I/O lines (as opposed to being
 * controlled by peripheral functions), the peripheral function defaults to PERIPH_A,
 * the pull-up resistor is enabled, and the pull-down resistor is disabled. All other
 * optional pin functions, which are not provided in this header file, are off upon reset.
 */
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

// Returns the given block's base address
uint32_t blockToBlockBase(int block) {
    return (block ? TC1 : TC0);
}

// Given a channel, returns the corresponding block's base address
uint32_t channelToBlockBase(int channelID) {
    return blockToBlockBase(channelToBlock(channelID));
}

// Returns the given channel's base address
uint32_t channelToChannelBase(int channelID) {
    uint32_t base = channelToBlockBase(channelID);
    uint32_t offset = (channelID % 3) * TC_CHANNEL_OFFSET;
    return base + offset;
}

void channelInit(int channelID, uint32_t clock, uint32_t mode) {
    TcChannel* channel = (TcChannel*) channelToChannelBase(channelID);
    (channel->TC_CCR).CLKEN   = 1;     // Enable clock
    (channel->TC_CMR).TCCLKS  = clock; // Set clock to desired clock
    (channel->TC_CMR).WAVE    = 1;     // Waveform mode
    (channel->TC_CMR).WAVESEL = mode;  // Set counting mode to desired mode
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


/////////////////////////////////////////////////////////////////////
// SPI Functions
/////////////////////////////////////////////////////////////////////

void spiInit(uint32_t clkdivide, uint32_t cpol, uint32_t ncpha) {
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
    SPI_REGS->SPI_CR.SPIEN = 1;

    //next setting the SPI mode register (p601) with the following:
        //master mode
        //fixed peripheral select
        //chip select lines directly connected to peripheral device
        //mode fault detection enabled
        //WDRBT disabled
        //LLB disabled
        //PCS = 0000 (Peripheral 0 selected), means NPCS[3:0] = 1110
        SPI_REGS->SPI_MR.MSTR = 1;

    //next setting the chip select register for peripheral 0 (p610)
    //ignoring delays

    //REG_SPI_CSR = (cpol<<0) | (ncpha<<1) | (clkdivide << 16);
        SPI_REGS->SPI_CSR0.SCBR = 0xFF;
}

char spiSendReceive(char send) {
    //Sends one byte over SPI and returns the received character
    SPI_REGS->SPI_TDR.TD = send;
    //Wait until Receive Data Register Full (RDRF, bit 0) and TXEMPTY (bit )
    while (!(SPI_REGS->SPI_SR.RDRF) || (SPI_REGS->SPI_SR.TXEMPTY));
    //After these status bits have gone high, the transaction is complete  
    return (char) (SPI_REGS->SPI_RDR.RD);
}

short spiSendReceive16(uint16_t send) {
    //sends one 16-bit short over SPI and returns the received short
    short rec;
    rec = spiSendReceive((send & 0xFF00) >> 8); // send data MSB first
    rec = (rec << 8) | spiSendReceive(send & 0xFF);
    return rec;
}


/////////////////////////////////////////////////////////////////////
// UART Functions
/////////////////////////////////////////////////////////////////////

/* Initialize UART. Note that pin PA9 is used as receive and pin PA10 
 * is used as transmit. samInit() must be called first.
 * parity:
 *   0: Even
 *   1: Odd
 *   2: Space (forced to 0)
 *   3: Mark (forced to 1)
 *   4: No (no parity)
 * Baud Rate =  MCK/(16*CD), CD is an unsigned short
 */
void uartInit(uint32_t parity, uint16_t CD) {
    pinMode(9,  PERIPH_A);           // Set URXD0 pin mode
    pinMode(10, PERIPH_A);           // Set ITXD0 pin mode

    UART_REGS->UART_CR.TXEN = 1;     // Enable transmitter
    UART_REGS->UART_CR.RXEN = 1;     // Enable receiver

    UART_REGS->UART_MR.PAR = parity; // Set parity
    UART_REGS->UART_BRGR   = CD;     // Set baud rate divider
}

// Transmits a character (1 byte) over UART
void uartTx(char data) {
    while (!(UART_REGS->UART_SR.TXRDY)); // Wait until previous data has been transmitted
    UART_REGS->UART_THR = data;          // Write data into holding register for transmit
}

// Returns a character (1 byte) received over UART
char uartRx() {
    while (!(UART_REGS->UART_SR.RXRDY)); // Wait until data has been received
    return (char) UART_REGS->UART_RHR;   // Return received data in holding register

}

/////////////////////////////////////////////////////////////////////
// General Functions
/////////////////////////////////////////////////////////////////////
void samInit() {
    //Many peripherals on the SAM4S are write protected: unless the correct password is written in a peripheral memory address, write access to peripheral control registers is disabled. This is done for security reasons, but is not necessary in this header file. In the first part of this function, we enable write access to the PMC, PIO, SPI, and UART by writing a password into the peripheral's Write Protect Mode Register (WPMR)

    //disabling PMC write protection (Password: "PMC")
    PMC_REGS->PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
    //disabling PIO write protection (Password: "PIO")
    PIOA_REGS->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
    PIOB_REGS->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
    //disabling SPI write protection (Password: "SPI")
    SPI_REGS->SPI_WPMR = SPI_WPMR_WPKEY_PASSWD;
    //There is no UART write protection

    //disabling timer write protection (Password: "TIM")
    TC0_REGS->TC_WPMR = TC_WPMR_WPKEY_PASSWD;
    TC1_REGS->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

    //We next need to supply a clock to these peripherals. For a given peripheral, clock is enabled by writing a 1 into a specific bit of the PMC Peripheral Clock Enable Register (PCER). There are two registers for the 34 peripherals. Peripheral - bit number mapping is given in p36: Peripheral Identifiers.

    //Activating clocks for UART 0 (PID 8), PIO A (PID 11), SPI (PID 21), TC0 (Timer/Counter CH0) (PID 23)

    PMC_REGS->PMC_PCER0 = 1 << ID_UART0;
    PMC_REGS->PMC_PCER0 = 1 << ID_PIOA;
    PMC_REGS->PMC_PCER0 = 1 << ID_PIOB;
    PMC_REGS->PMC_PCER0 = 1 << ID_SPI;
    PMC_REGS->PMC_PCER0 = 1 << ID_TC0;
    PMC_REGS->PMC_PCER0 = 1 << ID_TC1;
    PMC_REGS->PMC_PCER0 = 1 << ID_PWM;
    PMC_REGS->PMC_PCER0 = 1 << ID_ADC;
}

#endif
