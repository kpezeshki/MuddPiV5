/* SAM4S4B_wdt.h
 *
 * cferrarin@g.hmc.edu
 * kpezeshki@g.hmc.edu
 * 2/25/2019
 *
 * Contains base address locations, register structs, definitions, and functions for the WDT
 * Watch Dog Timer) peripheral of the SAM4S4B microcontroller. */

#ifndef SAM4S4B_WDT_H
#define SAM4S4B_WDT_H

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// RTC Base Address Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

#define WDT_BASE   (0x400E1450U) // WDT Base Address


////////////////////////////////////////////////////////////////////////////////////////////////////
// WDT Registers
////////////////////////////////////////////////////////////////////////////////////////////////////

// Bit field struct for the WDT_MR register
typedef struct {
    volatile uint32_t WDV       : 12;
    volatile uint32_t WDFIEN    : 1;
    volatile uint32_t WDRSTEN   : 1;
    volatile uint32_t WDRPROC   : 1;
    volatile uint32_t WDDIS     : 1;
    volatile uint32_t WDD       : 12;
    volatile uint32_t WDDBGHLT  : 1;
    volatile uint32_t WDIDLEHLT : 1;
    volatile uint32_t           : 2;
} WDT_MR_bits;

// Peripheral struct for the WDT peripheral
typedef struct {
    volatile uint32_t    WDT_CR; // (Wdt Offset: 0x00) Control Register
    volatile WDT_MR_bits WDT_MR; // (Wdt Offset: 0x04) Mode Register
    volatile uint32_t    WDT_SR; // (Wdt Offset: 0x08) Status Register
} Wdt;

// Pointer to an Rtc-sized chunk of memory at the RTC peripheral
#define WDT ((Wdt*) WDT_BASE)


////////////////////////////////////////////////////////////////////////////////////////////////////
// WDT Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

// None yet.
// (WDT does not have write protection).


////////////////////////////////////////////////////////////////////////////////////////////////////
// WDT User Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void wdtDisable() {
    WDT->WDT_MR.WDDIS = 1;
}


#endif
