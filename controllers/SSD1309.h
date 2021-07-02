/**
 * \file SSD1309.h
 * \brief Constants relating to SSD1309 LCD controller.
 * \author David Gautier (based on ST7565R.h by Andy Gock )
 *
 * Constants and functions specific to SSD1309.
 * Tested with EA OLEDL128-6GGA
 *
 *
 *
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



#ifndef SSD1309_H_
#define SSD1309_H_

/* Commands */
#define COMMAND_BYTE  0b10000000
#define DATA_BYTE  0b01000000

#define GLCD_LCD_WIDTH 128
#define GLCD_LCD_HEIGHT 64
#define SLAVE_ADDR 0x78>>1

#define SSD1309_DISPLAY_ON               0xAF /* 0b10101111 */
#define SSD1309_DISPLAY_OFF              0xAE /* 0b10101110 */
#define SSD1309_SET_ADDRESS_MODE         0x20
#define SSD1309_PAGE_ADDRESS_SET         0xB0
#define SSD1309_COLUMN_ADDRESS_SET_LOWER 0x00
#define SSD1309_COLUMN_ADDRESS_SET_UPPER 0x10
#define SSD1309_SET_START_LINE           0x40

#define SSD1309_NORMAL                   0xA6 /* 0b10100001 */
#define SSD1309_REVERSE                  0xA7 /* 0b10100001 */

#define SSD1309_DISPLAY_ALL_ON           0xA5
#define SSD1309_DISPLAY_NORMAL           0xA4

/* These functions on available on ST7565 implementation (for now) */

/* Private functions */
void glcd_set_column_upper(uint8_t addr);
void glcd_set_column_lower(uint8_t addr);
void glcd_test_data();

/** All display points on (native) */
void glcd_all_on(void);

/** Set to normal mode */
void glcd_normal(void);

/** Set start line/page */
void glcd_set_start_line(uint8_t addr);

/** Clear the display immediately, does not buffer */
void glcd_clear_now(void);

/** Show a black and white line pattern on the display */
void glcd_pattern(void);

/** Init SSD1309 controller / display */
void glcd_SSD1309_init(void);

#endif /* SSD1309_H_ */
