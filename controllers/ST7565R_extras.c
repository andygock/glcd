/**
 * \file ST7565R_extras.c
 * \brief Extra functions relating to ST7565R.
 * \author Andy Gock
 * \see ST7565R.h
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
#include "ST7565R.h"

#if defined(GLCD_CONTROLLER_ST7565R) || defined(USE_ARDUINO)

void glcd_all_on(void)
{
	glcd_command(ST7565R_DISPLAY_ALL_ON);
}

void glcd_normal(void)
{
	glcd_command(ST7565R_DISPLAY_NORMAL);
}

void glcd_set_column_upper(uint8_t addr)
{
	glcd_command(ST7565R_COLUMN_ADDRESS_SET_UPPER | (addr >> 4));
}

void glcd_set_column_lower(uint8_t addr)
{
	glcd_command(ST7565R_COLUMN_ADDRESS_SET_LOWER | (0x0f & addr));
}

void glcd_set_start_line(uint8_t addr)
{
	glcd_command( ST7565R_SET_START_LINE | (0x3F & addr)); /* 0x3F == 0b00111111 */
}

/** Clear the display immediately, does not buffer */
void glcd_clear_now(void)
{
	uint8_t page;
	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
		uint8_t col;
		glcd_set_y_address(page);
		glcd_set_x_address(0);
		for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
			glcd_data(0);
		}
	}
}

void glcd_pattern(void)
{
	uint8_t page;
	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
		uint8_t col;
		glcd_set_y_address(page);
		glcd_set_x_address(0);
		for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
			glcd_data( (col / 8 + 2) % 2 == 1 ? 0xff : 0x00 );
		}
	}
}


void glcd_ST7565R_init(void) {

#if defined(GLCD_INIT_NHD_C12832A1Z_FSW_FBW_3V3)

	/* Init sequence based on datasheet example code for NHD-C12832A1Z-FSW-FBW-3V3 */
	/* Datasheet says max SCK frequency 20MHz for this LCD */
	/* We use "reverse direction" for common output mode, as opposed to datasheet specifying "normal direction" */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x21); /* Internal resistor ratio, set to: 1 */
	glcd_set_contrast(40); /* Set contrast, value experimentally determined, can set to 6-bit value, 0 to 63 */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT)

	/* Init sequence based on datasheet example code for NHD-C12864A1Z-FSW-FBW-HTT */
	/* Datasheet says max SCK frequency 2.5MHz for this LCD */
	/* We use "reverse direction" for common output mode, as opposed to datasheet specifying "normal direction" */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x26); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(20); /* Set contrast, value experimentally determined */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M)

	/* Init sequence for NHD-C12864WC-FSW-FBW-3V3-M */

	glcd_command(ST7565R_RESET); /* Internal reset */
	glcd_command(0xa2); /* 1/9 bias */
	glcd_command(0xa0); /* ADC select, normal */
	glcd_command(0xc8); /* Com output reverse */
	glcd_command(0xa4); /* Display all points normal */
	glcd_command(0x40); /* Display start line set */
	glcd_command(0x25); /* Internal resistor ratio */
	glcd_set_contrast(45); /* Set contrast value, experimentally determined, value 0 to 63 */
	glcd_command(0x2f); /* Power controller set */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_ZOLEN_12864_FFSSWE_NAA)

	/* Init sequence for Zolen 128x64 module with
	 * size 40x35mm. Chip ST7567 */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa3); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x24); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(20); /* Set contrast, value experimentally determined, value 0 to 63 */
	glcd_command(0xaf); /* Display on */

#else

	/* Default init sequence */
	/* Currently just set the same as GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x26); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(20); /* Set contrast, value experimentally determined, value 0 to 63 */
	glcd_command(0xaf); /* Display on */

#endif

}

#endif /* defined(GLCD_CONTROLLER_ST7565R) */