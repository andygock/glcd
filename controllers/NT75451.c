/**
	\file NT75451.c
	\author Andy Gock
	\brief Function specific to NT75451 controller.
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

#if defined(GLCD_CONTROLLER_NT75451)

#include "../glcd.h"

void glcd_command(uint8_t c)
{
	GLCD_RS_LOW();
	glcd_parallel_write(c);
	GLCD_RS_HIGH();	
}

void glcd_data(uint8_t c)
{
	GLCD_RS_HIGH();
	glcd_parallel_write(c);
	GLCD_RS_LOW();
}

void glcd_set_contrast(uint8_t val) {
}

void glcd_power_down(void)
{
}

void glcd_power_up(void)
{
}

void glcd_set_y_address(uint8_t y)
{
	/** Code by NGX Technologies */
	glcd_command(0xB0 | (y > GLCD_NUMBER_OF_BANKS ? GLCD_NUMBER_OF_BANKS : y));
}

void glcd_set_x_address(uint8_t x)
{
	/** Code by NGX Technologies */
	uint8_t lsb, msb;
	
	msb	= (((x & 0xF0) >> 4)| 0x10);
	lsb	= (x & 0x0F);
	
	glcd_command(lsb);
	glcd_command(msb);	
}

/* Write screen buffer to display, within bounding box only */
void glcd_write()
{
	uint8_t bank;
	
	for (bank = 0; bank < GLCD_NUMBER_OF_BANKS; bank++) {
		/* Each bank is a single row 8 bits tall */
		uint8_t column;		
		
		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; /* Skip the entire bank */
		}
		
		if (glcd_bbox_selected->y_max < bank*8) {
			break;    /* No more banks need updating */
		}
		
		glcd_set_y_address(bank);
		glcd_set_x_address(glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			glcd_data( glcd_buffer_selected[GLCD_NUMBER_OF_COLS * bank + column] );
		}
	}

	/* Display updated, we can reset the bounding box */
	glcd_reset_bbox();
	
}

void glcd_NT75451_init(void) {
	/* Initialise sequence - code by NGX Technologies */
	glcd_command(0xE2);  /*	S/W RESWT               */
	glcd_command(0xA0);  /*	ADC select              */
	glcd_command(0xC8);  /*	SHL Normal              */
	glcd_command(0xA3);  /*	LCD bias                */
	glcd_command(0x2F);  /*	Power control           */
	glcd_command(0x22);  /*	reg resistor select     */
	glcd_command(0x40);  /*	Initial display line 40 */
	glcd_command(0xA4);  /*	Normal display          */
	glcd_command(0xA6);  /*	Reverce display a7      */
	glcd_command(0x81);  /*	Ref vg select mode      */
	glcd_command(0x3f);  /*	Ref vg reg select       */
	glcd_command(0xB0);  /*	Set page address        */
	glcd_command(0x10);  /*	Set coloumn addr MSB    */
	glcd_command(0x00);  /*	Set coloumn addr LSB    */
	glcd_command(0xAF);  /*	Display ON              */
}

#endif

