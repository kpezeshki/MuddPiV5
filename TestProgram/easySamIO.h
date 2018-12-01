// cferrarin@g.hmc.edu
// kpezeshki@g.hmc.edu
// 11/30/2018

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

/* Useful things from CMSIS files:

/////////////////////////////////////////////////////////////////////
// Device characteristics
/////////////////////////////////////////////////////////////////////

#define CHIP_FREQ_SLCK_RC_MIN           (20000UL)
#define CHIP_FREQ_SLCK_RC               (32000UL)
#define CHIP_FREQ_SLCK_RC_MAX           (44000UL)
#define CHIP_FREQ_MAINCK_RC_4MHZ        (4000000UL)
#define CHIP_FREQ_MAINCK_RC_8MHZ        (8000000UL)
#define CHIP_FREQ_MAINCK_RC_12MHZ       (12000000UL)
#define CHIP_FREQ_CPU_MAX               (64000000UL)
#define CHIP_FREQ_XTAL_32K              (32768UL)
#define CHIP_FREQ_XTAL_12M              (12000000UL)

/////////////////////////////////////////////////////////////////////
// Peripheral ID definitions
/////////////////////////////////////////////////////////////////////

#define ID_SUPC   ( 0) /**< \brief Supply Controller (SUPC) 
#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) 
#define ID_RTC    ( 2) /**< \brief Real Time Clock (RTC) 
#define ID_RTT    ( 3) /**< \brief Real Time Timer (RTT) 
#define ID_WDT    ( 4) /**< \brief Watchdog Timer (WDT) 
#define ID_PMC    ( 5) /**< \brief Power Management Controller (PMC) 
#define ID_EFC    ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) 
#define ID_UART0  ( 8) /**< \brief UART 0 (UART0) 
#define ID_UART1  ( 9) /**< \brief UART 1 (UART1) 
#define ID_PIOA   (11) /**< \brief Parallel I/O Controller A (PIOA) 
#define ID_PIOB   (12) /**< \brief Parallel I/O Controller B (PIOB) 
#define ID_USART0 (14) /**< \brief USART 0 (USART0) 
#define ID_USART1 (15) /**< \brief USART 1 (USART1) 
#define ID_HSMCI  (18) /**< \brief Multimedia Card Interface (HSMCI) 
#define ID_TWI0   (19) /**< \brief Two Wire Interface 0 (TWI0) 
#define ID_TWI1   (20) /**< \brief Two Wire Interface 1 (TWI1) 
#define ID_SPI    (21) /**< \brief Serial Peripheral Interface (SPI) 
#define ID_SSC    (22) /**< \brief Synchronous Serial Controler (SSC) 
#define ID_TC0    (23) /**< \brief Timer/Counter 0 (TC0) 
#define ID_TC1    (24) /**< \brief Timer/Counter 1 (TC1) 
#define ID_TC2    (25) /**< \brief Timer/Counter 2 (TC2) 
#define ID_ADC    (29) /**< \brief Analog To Digital Converter (ADC) 
#define ID_DACC   (30) /**< \brief Digital To Analog Converter (DACC) 
#define ID_PWM    (31) /**< \brief Pulse Width Modulation (PWM) 
#define ID_CRCCU  (32) /**< \brief CRC Calculation Unit (CRCCU) 
#define ID_ACC    (33) /**< \brief Analog Comparator (ACC) 
#define ID_UDP    (34) /**< \brief USB Device Port (UDP) 
*/

/* Development checklist:
 * PIO:   Add support for PIOB              DONE
 * PIO:   Final pass                        DONE
 * TIMER: Add support for TC1               IN PROGRESS
 * TIMER: Refine delays, add delay_us()     NOT STARTED
 * TIMER: Final pass                        NOT STARTED
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

/////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////

#define MCK				4000000
#define TIMER_CLOCK1	(MCK / 2)
#define TIMER_CLOCK4	(MCK / 128)

/////////////////////////////////////////////////////////////////////
// Base Address Definitions
/////////////////////////////////////////////////////////////////////

#define SPI        (0x40008000U) /**< \brief (SPI       ) Base Address */
#define TC0        (0x40010000U) /**< \brief (TC0       ) Base Address */
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
    uint32_t PIO_ABCDSR[2];  /**< \brief (Pio Offset: 0x0070) Peripheral Select Register */
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

#define REG_TC0_CCR  (*(  volatile unsigned int *)0x40010000U) /**< \brief (TC0) Channel Control Register */
#define REG_TC0_CMR  (*(  volatile unsigned int *)0x40010004U) /**< \brief (TC0) Channel Mode Register */
#define REG_TC0_SMMR (*(  volatile unsigned int *)0x40010008U) /**< \brief (TC0) Stepper Motor Mode Register */
#define REG_TC0_CV   (*(  volatile unsigned int *)0x40010010U) /**< \brief (TC0) Counter Value Register */
#define REG_TC0_RA   (*(  volatile unsigned int *)0x40010014U) /**< \brief (TC0) Register A Register */
#define REG_TC0_RB   (*(  volatile unsigned int *)0x40010018U) /**< \brief (TC0) Register B Register */
#define REG_TC0_RC   (*(  volatile unsigned int *)0x4001001CU) /**< \brief (TC0) Register C Register */
#define REG_TC0_SR   (*(  volatile unsigned int *)0x40010020U) /**< \brief (TC0) Status Register */
#define REG_TC0_IER  (*(  volatile unsigned int *)0x40010024U) /**< \brief (TC0) Interrupt Enable Register */
#define REG_TC0_IDR  (*(  volatile unsigned int *)0x40010028U) /**< \brief (TC0) Interrupt Disable Register */
#define REG_TC0_IMR  (*(  volatile unsigned int *)0x4001002CU) /**< \brief (TC0) Interrupt Mask Register */

#define REG_TC_BCR   (*(  volatile unsigned int *)0x400100C0U) /**< \brief (TC) Block Control Register */
#define REG_TC_BMR   (*(  volatile unsigned int *)0x400100C4U) /**< \brief (TC) Block Mode Register */
#define REG_TC_QIER  (*(  volatile unsigned int *)0x400100C8U) /**< \brief (TC) QDEC Interrupt Enable Register */
#define REG_TC_QIDR  (*(  volatile unsigned int *)0x400100CCU) /**< \brief (TC) QDEC Interrupt Disable Register */
#define REG_TC_QIMR  (*(  volatile unsigned int *)0x400100D0U) /**< \brief (TC) QDEC Interrupt Mask Register */
#define REG_TC_QISR  (*(  volatile unsigned int *)0x400100D4U) /**< \brief (TC) QDEC Interrupt Status Register */
#define REG_TC_FMR   (*(  volatile unsigned int *)0x400100D8U) /**< \brief (TC) Fault Mode Register */
#define REG_TC_WPMR  (*(  volatile unsigned int *)0x400100E4U) /**< \brief (TC) Write Protect Mode Register */

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


void samInit() {
    //Many peripherals on the SAM4S are write protected: unless the correct password is written in a peripheral memory address, write access to peripheral control registers is disabled. This is done for security reasons, but is not necessary in this header file. In the first part of this function, we enable write access to the PMC, PIO, SPI, and UART by writing a password into the peripheral's Write Protect Mode Register (WPMR)


	//disabling PMC write protection (Password: "PMC")
    REG_PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	//disabling PIO write protection (Password: "PIO")
    REG_PIOA_WPMR = PIO_WPMR_WPKEY_PASSWD;
	//disabling SPI write protection (Password: "SPI")
    REG_SPI_WPMR = SPI_WPMR_WPKEY_PASSWD;
	//There is no UART write protection

	//disabling timer write protection (Password: "TIM")
    REG_TC_WPMR = TC_WPMR_WPKEY_PASSWD;

    //We next need to supply a clock to these peripherals. For a given peripheral, clock is enabled by writing a 1 into a specific bit of the PMC Peripheral Clock Enable Register (PCER). There are two registers for the 34 peripherals. Peripheral - bit number mapping is given in p36: Peripheral Identifiers.

    //Activating clocks for UART 0 (PID 8), PIO A (PID 11), SPI (PID 21), TC0 (Timer/Counter CH0) (PID 23)

	REG_PMC_PCER0 |= (1<<8);
	REG_PMC_PCER0 |= (1<<11);
	REG_PMC_PCER0 |= (1<<21);
	REG_PMC_PCER0 |= (1<<23);
}


/////////////////////////////////////////////////////////////////////
// PIO Functions
/////////////////////////////////////////////////////////////////////

#define LOW         0 // Value to write a pin low (0 V)
#define HIGH        1 // Value ot write a pin high (3.3 V)

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
Pio* portToBase(int port) {
    uint32_t base = port ? PORTB : PORTA;
    return (Pio*) (uintptr_t) base; // Might be <return (Pio*) (uintptr_t) base;>
}

// Given a pin, returns the corresponding port's base address
Pio* pinToBase(int pin) {
    return portToBase(pinToPort(pin));
}

// Note: Upon reset, pins are configured as input I/O lines (as opposed to being
// controlled by peripheral funcitons), the peripheral function defaults to PERIPH_A,
// the pull-up resistor is enabled, and the pull-down resistor is disabled. All other
// optional pin functions, which are not provided in this header file, are off upon reset.
void pinMode(int pin, int function) {
    Pio* base = pinToBase(pin);
    int offset = pin % 32;

    switch (function) {
        case INPUT:
            break;
        case OUTPUT:
            base->PIO_OER     |=  (1 << offset); // Configures an I/O line as an output
            break;
        case PERIPH_A:
            base->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            base->PIO_ABCDSR1 &= ~(1 << offset); // Sets the peripheral which controls a pin
            base->PIO_ABCDSR2 &= ~(1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_B:
            base->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            base->PIO_ABCDSR1 |=  (1 << offset); // Sets the peripheral which controls a pin
            base->PIO_ABCDSR2 &= ~(1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_C:
            base->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            base->PIO_ABCDSR1 &= ~(1 << offset); // Sets the peripheral which controls a pin
            base->PIO_ABCDSR2 |=  (1 << offset); // Sets the peripheral which controls a pin
            break;
        case PERIPH_D:
            base->PIO_PDR     |=  (1 << offset); // Sets a pin to be peripheral-controlled
            base->PIO_ABCDSR1 |=  (1 << offset); // Sets the peripheral which controls a pin
            base->PIO_ABCDSR2 |=  (1 << offset); // Sets the peripheral which controls a pin
            break;
        case PULL_DOWN:
            base->PIO_PUDR    |=  (1 << offset); // Disables the pull-up resistor
            base->PIO_PPDER   |=  (1 << offset); // Enables the pull-down resistor
        case FLOATING:
            base->PIO_PUDR    |=  (1 << offset); // Disables the pull-down resistor
    }
}

// Reads the digital voltage on a pin configured as an input I/O line
int digitalRead(int pin) {
    Pio* base = pinToBase(pin);
    int offset = pin % 32;
    return ((base->PIO_PDSR) >> offset) & 1;
}

// Writes a digital voltage to a pin configured as an output I/O line
void digitalWrite(int pin, int val) {
    Pio* base = pinToBase(pin);
    int offset = pin % 32;
    if (val) {
        base->PIO_SODR |= (1 << offset);
    } else {
        base->PIO_CODR |= (1 << offset);
    }
}

// Switches the digital voltage on a pin configured as in output I/O line
void toggle(int pin) {
    int currentVal = digitalRead(pin);
    digitalWrite(pin, !currentVal);
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
    pinMode(11, A);
    pinMode(12, A);
    pinMode(13, A);
    pinMode(14, A);

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
--------TIMER METHODS-------------
----------------------------*/

void timerInit() {
	// Enable clock to channel
	REG_TC0_CCR	   &= ~(1 << 1);
    REG_TC0_CCR	   |= 1;
	
	REG_TC0_CMR    |= (1 << 15); // WAVE = 1 (waveform mode)
	REG_TC0_CMR	   |= (1 << 14); // WAVESEL = 2 (UP_RC waveform)
}

// Works until 2097 ms
// Resolution of 32 us
void delay_ms(int num) {
	REG_TC0_CMR |= 0x3; //0b11; // Using TIMER_CLOCK4
	REG_TC0_RC   = (unsigned long) (TIMER_CLOCK4 * (((float) num) / 1000)); // Compare value
	REG_TC0_CCR |= (1 << 2); // Reset counter
	while (!((REG_TC0_SR >> 4) & 1)); // Delay until match
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
	pinMode(9, A);		  // Set URXD0 pin mode
	pinMode(10, A);		  // Set ITXD0 pin mode

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

#endif
