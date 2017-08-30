/**
   \file avr8.c
   \brief Functions relating to Atmel AVR 8-bit AVRs with Arduino.
          For use with GNU toolchain
   \author Andy Gock

 */

/*
	Copyright (c) 2012, Andy Gock

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of Andy Gock nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL ANDY GOCK BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../glcd.h"
#include "../controllers/PCD8544.h"
#include "../controllers/ST7565R.h"
#include "../controllers/NT75451.h" /* not implemented */
#include "avr8.h"

#if defined(USE_ARDUINO)

#include <Arduino.h>

/* Extra global variables used for Arduino implementation */
struct glcd_pinmap_t glcd_pinmap;

void glcd_select_lcd_controller(uint8_t controller) {
	glcd_pinmap.controller = controller;
}

void glcd_set_pinmap(uint8_t pin_type, volatile uint8_t *port, uint8_t pin) {
	glcd_pinmap.port[pin_type] = port;
	glcd_pinmap.pin[pin_type] = pin;
}

/* Convert a bitmask to a bit number */
uint8_t glcd_bitmask_to_bitnumber(uint8_t mask) {
	/*
		in: 0b00000001 out: 0
		in: 0b00000010 out: 1
		in: 0b00000100 out: 2
		...
		output can be 0 to 7 - or 0xff if error (case of input == 0)
	 */

	uint8_t i;
	for (i=0; i<8; i++) {
		if (mask & (1<<i)) {
			return i;
		}
	}
	return 0xFF; // mask == 0 - user should not pass 0 as mask
}


/* Alternative to glcd_set_pin(), but use digital pin numbers, more user friendly */
void glcd_set_pin(uint8_t name, uint8_t arduino_pin) {
	/* Macros from <Arduino.h> */
	volatile uint8_t port = digitalPinToPort(arduino_pin);
	uint8_t bit_mask = digitalPinToBitMask(arduino_pin);
	glcd_set_pinmap(name, &port, glcd_bitmask_to_bitnumber(bit_mask));
}


void glcd_init(void)
{

	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {

		/* Set pin directions */

		/*
		 * Set up SPI for AVR8
		 * Note: AVR's SS pin must be set to output, regardless of whether we
		 * actually use it. This is a requirement of SPI master mode.
		 */
		sbi(DDR(*glcd_pinmap.port[PORT_AVR_SS]), glcd_pinmap.pin[PORT_AVR_SS]);

		/*
		 *  Set MOSI, Master SS, SCK to output (otherwise SPI won't work)
		 *  Must be done even if native SS pin not used
		 */
		sbi(DDR(*glcd_pinmap.port[PORT_MOSI]), glcd_pinmap.pin[PORT_MOSI]);
		sbi(DDR(*glcd_pinmap.port[PORT_SS]), glcd_pinmap.pin[PORT_SS]);
		sbi(DDR(*glcd_pinmap.port[PORT_SCK]), glcd_pinmap.pin[PORT_SCK]);

		/* Set SS, DC and RST pins to output */
		sbi(DDR(*glcd_pinmap.port[PORT_SS]), glcd_pinmap.pin[PORT_SS]);
		sbi(DDR(*glcd_pinmap.port[PORT_DC]), glcd_pinmap.pin[PORT_DC]);
		sbi(DDR(*glcd_pinmap.port[PORT_RST]), glcd_pinmap.pin[PORT_RST]);

		/* Deselect LCD */
		GLCD_DESELECT();

		/*
		 * Max allowed SPI clock is 4 MHz from datasheet.
		 * Enable SPI, set master mode and clock rate to /4 (4MHz with F_CPU=8MHz)
		 */
		SPCR = (1<<SPE)|(1<<MSTR);
		SPSR = 0;

		glcd_PCD8544_init();

		/* Select screen buffer */
		glcd_select_screen(glcd_buffer,&glcd_bbox);

		/* Clear screen, we are now ready to go */
		glcd_clear();

	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {

		/* Set up GPIO directions */

		/*
		 * Set up SPI for AVR8
		 * Note: AVR's SS pin must be set to output, regardless of whether we
		 * actually use it. This is a requirement of SPI master mode.
		 */
		sbi(DDR(*glcd_pinmap.port[PORT_AVR_SS]), glcd_pinmap.pin[PORT_AVR_SS]);

		/*
		 *  Set MOSI, Master SS, SCK to output (otherwise SPI won't work)
		 *  Must be done even if native SS pin not used
		 */
		sbi(DDR(*glcd_pinmap.port[PORT_MOSI]), glcd_pinmap.pin[PORT_MOSI]);
		sbi(DDR(*glcd_pinmap.port[PORT_SS]), glcd_pinmap.pin[PORT_SS]);
		sbi(DDR(*glcd_pinmap.port[PORT_SCK]), glcd_pinmap.pin[PORT_SCK]);

		/* Set SS, DC and RST pins to output */
		sbi(DDR(*glcd_pinmap.port[PORT_SS]), glcd_pinmap.pin[PORT_SS]);
		sbi(DDR(*glcd_pinmap.port[PORT_A0]), glcd_pinmap.pin[PORT_A0]);
		sbi(DDR(*glcd_pinmap.port[PORT_RST]), glcd_pinmap.pin[PORT_RST]);


		/*
		 * Set MISO as input with pullup. This needs to be set for
		 * SPI to work, even though we never use or read it.
		 */
		cbi(DDR(*glcd_pinmap.port[PORT_MISO]), glcd_pinmap.pin[PORT_MISO]);
		sbi(*glcd_pinmap.port[PORT_MISO], glcd_pinmap.pin[PORT_MISO]);


		/* Init SS pin high (i.e LCD deselected) */
		sbi(*glcd_pinmap.port[PORT_SS], glcd_pinmap.pin[PORT_SS]);

		/* Deselect LCD */
		GLCD_DESELECT();

		/* MSB first, double speed, SPI mode 0 */
		SPCR = (1<<SPE) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA);
		sbi(SPSR,SPI2X);

		/* Enable interrupts */
		sei();

		delay_ms(30); /* Example in datasheet does this (20ms) */

		glcd_ST7565R_init();

		glcd_all_on();

		delay_ms(500);
		glcd_normal();

		glcd_set_start_line(0);
		glcd_clear_now();

		glcd_select_screen(glcd_buffer,&glcd_bbox);

		glcd_clear();

	} else {

		/* Controller not supported - halt or do something like that? */

	}

}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SPDR = c;
	while(!(SPSR & (1<<SPIF))); /* wait until transmission is complete */
	GLCD_DESELECT();
}

void glcd_reset(void)
{
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}

void GLCD_SELECT() {
	cbi(*glcd_pinmap.port[PORT_SS], glcd_pinmap.pin[PORT_SS]);
}

void GLCD_DESELECT() {
	sbi(*glcd_pinmap.port[PORT_SS], glcd_pinmap.pin[PORT_SS]);
}

void GLCD_DC_LOW() {
	cbi(*glcd_pinmap.port[PORT_DC], glcd_pinmap.pin[PORT_DC]);
}

void GLCD_DC_HIGH() {
	sbi(*glcd_pinmap.port[PORT_DC], glcd_pinmap.pin[PORT_DC]);
}

void GLCD_RESET_LOW() {
	cbi(*glcd_pinmap.port[PORT_RST], glcd_pinmap.pin[PORT_RST]);
}

void GLCD_RESET_HIGH() {
	sbi(*glcd_pinmap.port[PORT_RST], glcd_pinmap.pin[PORT_RST]);
}

void GLCD_A0_LOW() {
	cbi(*glcd_pinmap.port[PORT_A0], glcd_pinmap.pin[PORT_A0]);
}

void GLCD_A0_HIGH() {
	sbi(*glcd_pinmap.port[PORT_A0], glcd_pinmap.pin[PORT_A0]);
}


#endif /* defined(USE_ARDUINO) */
