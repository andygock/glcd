/**
 * \file PCD8544.c
 * \brief Functions relating to PCD8544 LCD Controller (Nokia 5110 LCD).
 * \author Andy Gock
 * \see glcd.h
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

#if defined(GLCD_CONTROLLER_PCD8544)

#include "../glcd.h"

void glcd_command(uint8_t c)
{
	GLCD_DC_LOW();
	glcd_spi_write(c);
}

void glcd_data(uint8_t c)
{
	GLCD_DC_HIGH();
	glcd_spi_write(c);
}

void glcd_set_contrast(uint8_t val) {
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);
	glcd_command(PCD8544_SET_VOP | (val&0x7f));
	glcd_command(PCD8544_FUNCTION_SET);
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
}

void glcd_power_down(void)
{
	/* First, fill RAM with zeroes to ensure minimum specified current consumption */
	glcd_clear();

	/* Power down */
	glcd_command(PCD8544_FUNCTION_SET|PCD8544_POWER_DOWN);
}

void glcd_power_up(void)
{
	glcd_command(PCD8544_FUNCTION_SET);
}

void glcd_set_y_address(uint8_t y)
{
	glcd_command(PCD8544_SET_Y_ADDRESS|(y > 5 ? 5 : y));
}

void glcd_set_x_address(uint8_t x)
{
	glcd_command(PCD8544_SET_X_ADDRESS|(x & 0x7f));
}

void glcd_write()
{
	uint8_t bank;

	for (bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
		/* Each bank is a single row 8 bits tall */
		uint8_t column;

		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; /* Skip the entire bank */
		}

		if (glcd_bbox_selected->y_max < bank*8) {
			break;    /* No more banks need updating */
		}

		glcd_command(PCD8544_SET_Y_ADDRESS | bank);
		glcd_command(PCD8544_SET_X_ADDRESS | glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			glcd_data( glcd_buffer_selected[PCD8544_MAX_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();

}

void glcd_PCD8544_init(void) {

	glcd_reset();
	
	/* Get into the EXTENDED mode! */
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);

	/* LCD bias select (4 is optimal?) */
	glcd_command(PCD8544_SET_BIAS | 0x2);

	/* Set VOP (affects contrast) */
	/* Experimentally determined, play with this figure until contrast looks nice */
#if defined(PCD8544_CONTRAST)
	glcd_command(PCD8544_SET_VOP | PCD8544_CONTRAST); 
#else
	glcd_command(PCD8544_SET_VOP | 80);
#endif
	
	/* Back to standard instructions */
	glcd_command(PCD8544_FUNCTION_SET);

	/* Normal mode */
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
}

#endif
