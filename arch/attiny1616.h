// arch/attiny1616.h: attiny1616 support header
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// FIXME: remove this
#define AVRXMEGA3

////////// clock speed / delay stuff //////////

#define F_CPU  10000000UL
#define BOGOMIPS  (F_CPU/4700)
#define DELAY_ZERO_TIME  1020

///// clock dividers
// this should work, but needs further validation
inline void clock_prescale_set(uint8_t n);

typedef enum
{
    // Actual clock is 20 MHz, but assume that 10 MHz is the top speed and work from there
    // TODO: measure PWM speed and power use at 1.25/2.5/5/10 MHz, to determine which speeds are optimal
    clock_div_1 =   (CLKCTRL_PDIV_2X_gc  | CLKCTRL_PEN_bm), // 10 MHz
    clock_div_2 =   (CLKCTRL_PDIV_4X_gc  | CLKCTRL_PEN_bm), // 5 MHz
    clock_div_4 =   (CLKCTRL_PDIV_8X_gc  | CLKCTRL_PEN_bm), // 2.5 MHz
    clock_div_8 =   (CLKCTRL_PDIV_16X_gc | CLKCTRL_PEN_bm), // 1.25 MHz
    clock_div_16 =  (CLKCTRL_PDIV_32X_gc | CLKCTRL_PEN_bm), // 625 kHz
    clock_div_32 =  (CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm), // 312 kHz, max without changing to the 32 kHz ULP
    clock_div_64 =  (CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm), // 312 kHz
    clock_div_128 = (CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm), // 312 kHz
    clock_div_256 = (CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm)  // 312 kHz
} clock_div_t;


////////// ADC voltage / temperature //////////

#define hwdef_set_admux_therm  mcu_set_admux_therm
inline void mcu_set_admux_therm();

#define hwdef_set_admux_voltage mcu_set_admux_voltage
inline void mcu_set_admux_voltage();

inline void mcu_adc_sleep_mode();

inline void mcu_adc_start_measurement();

inline void mcu_adc_on();

inline void mcu_adc_off();

#define ADC_vect  ADC0_RESRDY_vect
inline void mcu_adc_vect_clear();

// read ADC differently for temperature and voltage
#define MCU_ADC_RESULT_PER_TYPE

inline uint16_t mcu_adc_result_temp();

inline uint16_t mcu_adc_result_volts();

inline uint8_t mcu_adc_lsb();


////////// WDT //////////

inline void mcu_wdt_active();

inline void mcu_wdt_standby();

inline void mcu_wdt_stop();

// *** Note for the AVRXMEGA3 (1-Series, eg 816 and 817), the WDT 
// is not used for time-based interrupts.  A new peripheral, the 
// Periodic Interrupt Timer ("PIT") is used for this purpose.

#define WDT_vect  RTC_PIT_vect
inline void mcu_wdt_vect_clear();


////////// PCINT - pin change interrupt (e-switch) //////////

// set these in hwdef
//#define SWITCH_PORT  PINA
//#define SWITCH_VECT  PCINT0_vect

inline void mcu_switch_vect_clear();

inline void mcu_pcint_on();

inline void mcu_pcint_off();


////////// misc //////////

void reboot();

