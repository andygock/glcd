#ifndef ARDUINO_AVR8_H
#define ARDUINO_AVR8_H

#include "../glcd.h"

#if defined(USE_ARDUINO)

/*

This isn't a very optimum way of using PGM space and SRAM, but it is
beginner friendly and suitable for Arduino implementation.

Lots of SRAM is wasted with this method! glcd_pinmap_t alone costs 17 bytes

Ideal beginner friendly initialisation sequence example:

	glcd_select_lcd_controller(GLCD_TYPE_PCD8544)
	glcd_set_pin(AVR_SS, &PORTB, 0);
	glcd_set_pin(PORT_MOSI, &PORTB, 2);
	glcd_set_pin(PORT_MISO, &PORTB, 3);
	glcd_set_pin(PORT_SCK, &PORTB, 1);
	glcd_set_pin(PORT_SS, &PORTA, 5);
	glcd_set_pin(PORT_DC, &PORTB, 5);
	glcd_set_pin(PORT_RST, &PORTB, 4);
	glcd_init();

Notes and references:

Passing AVR port as function argument
- http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_port_pass
- http://www.avrfreaks.net/forum/passing-port-argument

*/

#ifndef _BITHELPERS_
#define _BITHELPERS_
#define sbi(var, mask) ((var) |= _BV(mask))
#define cbi(var, mask) ((var) &= ~(_BV(mask)))
#define DDR(x) (*(&x - 1))
#define PIN(x) (*(&x - 2))
#endif

/* pin type as uint8_t */
#define PORT_AVR_SS 0
#define PORT_MOSI 1
#define PORT_MISO 2
#define PORT_SCK 3
#define PORT_SS 4
#define PORT_DC 5 /* GLCD_TYPE_PCD8544 only */
#define PORT_A0 5 /* GLCD_TYPE_ST7565R only */
#define PORT_RST 6

/* Maximum number of IO pins that may be used */
#define NUMBER_OF_PINS 8

/* glcd_pinmap_t.controller - unit8_t */
#define GLCD_TYPE_PCD8544 0
#define GLCD_TYPE_ST7565R 1

/* pin map users generic pin numbers 0, 1, 2... */
struct glcd_pinmap_t {
	uint8_t controller;
	volatile uint8_t *port[NUMBER_OF_PINS];
	uint8_t pin[NUMBER_OF_PINS];
};

/* Global variables */
extern struct glcd_pinmap_t glcd_pinmap;

/* Function prototypes */

void glcd_select_lcd_controller(uint8_t controller);
void glcd_set_pinmap(uint8_t pin_type, volatile uint8_t *port, uint8_t pin_mask);
uint8_t glcd_bitmask_to_bitnumber(uint8_t mask);
void glcd_set_pin(uint8_t name, uint8_t arduino_pin);

void GLCD_SELECT();
void GLCD_DESELECT();
void GLCD_DC_LOW();
void GLCD_DC_HIGH();
void GLCD_RESET_LOW();
void GLCD_RESET_HIGH();
void GLCD_A0_LOW();
void GLCD_A0_HIGH();

#endif /* ARDUINO_ARCH_AVR */

#endif