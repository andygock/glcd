/**
   \file text_tiny.c
   \brief Functions relating to using tiny 5x7 text fonts.
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

#include "glcd.h"

#if defined(GLCD_DEVICE_AVR8)
void glcd_tiny_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char)
#else
void glcd_tiny_set_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char)
#endif
{
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = STANG;
}

void glcd_tiny_draw_char(uint8_t x, uint8_t line, char c)
{
	uint8_t i;
	
	/* Only works for fonts < 8 bits in height */
	if (font_current.height >= 8) {
		return;
	}
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	if ( line >= GLCD_LCD_HEIGHT / (font_current.height + 1) ) {
		return;
	}		
	if ( (x+font_current.width) >= GLCD_LCD_WIDTH ) {
		return;
	}		
	
	glcd_update_bbox(x, line*(font_current.height + 1), x+font_current.width, line*(font_current.height + 1) + (font_current.height + 1));
	
	for ( i = 0; i < font_current.width; i++ ) {
#if defined(GLCD_DEVICE_AVR8)		
		glcd_buffer_selected[x + (line * GLCD_LCD_WIDTH)] = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#else
		glcd_buffer_selected[x + (line * GLCD_LCD_WIDTH)] = *( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#endif
		x++;
	}
}

void glcd_tiny_draw_string(uint8_t x, uint8_t line, char *str)
{
	if (font_current.height >= 8) {
		return;
	}
	while (*str) {
		glcd_tiny_draw_char(x, line, *str++);
		x += (font_current.width + 1);
		if ((x + font_current.width + 1) > GLCD_LCD_WIDTH) {
			x = 0; /* Ran out of this line */
			line++;
		}
		if (line >= (GLCD_LCD_HEIGHT/(font_current.height + 1)))
			return; /* Ran out of space :( */
	}
}

#if defined(GLCD_DEVICE_AVR8)
void glcd_tiny_draw_string_P(uint8_t x, uint8_t line, PGM_P str)
#else
void glcd_tiny_draw_string_P(uint8_t x, uint8_t line, const char *str)
#endif
{
	if (font_current.height >= 8) {
		return;
	}
	while (1) {
#if defined(GLCD_DEVICE_AVR8)
		char c = pgm_read_byte(str++);
#else
		char c = *(str++);
#endif
		if (!c)
			return;	
				
		glcd_tiny_draw_char(x, line, c);
		
		x += (font_current.width + 1);
		if ((x + font_current.width + 1) > GLCD_LCD_WIDTH) {
			x = 0; /* Ran out of this line */
			line++;
		}
		if (line >= (GLCD_LCD_HEIGHT/(font_current.height + 1)))
			return; /* Ran out of space :( */
	}	
}

void glcd_tiny_draw_string_ammend(char *str) {
	glcd_scroll_line();
	glcd_tiny_draw_string(0, (GLCD_LCD_HEIGHT/8-1), str);
	glcd_write();
}

void glcd_tiny_draw_string_ammend_P(const char *str) {
	glcd_scroll_line();
	glcd_tiny_draw_string_P(0, (GLCD_LCD_HEIGHT/8-1), str);
	glcd_write();
}

void glcd_tiny_invert_line(uint8_t line)
{
	glcd_invert_area(0,line*8,GLCD_LCD_WIDTH-1,8);
}

void glcd_tiny_draw_char_xy(uint8_t x, uint8_t y, char c)
{
	uint8_t i;
	uint8_t xvar, yvar;
	uint8_t dat;
	
	/* Only works for fonts < 8 bits in height */
	
	/* Check all important bounds requirements are okay */
	if ( (y >= GLCD_LCD_HEIGHT) || ((x+font_current.width) >= GLCD_LCD_WIDTH) || (font_current.height >= 8) || font_current.table_type != STANG) {
		return;
	}		
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	
	xvar = x;
	
	for ( i = 0; i < font_current.width; i++ ) {
#if defined(GLCD_DEVICE_AVR8)			
		dat = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#else
		dat = *( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#endif
		for (yvar = 0; yvar < font_current.height; yvar++) {
			glcd_set_pixel(xvar,y+yvar, (dat & (1<<yvar) ? 1 : 0) );
		}
		xvar++;
	}
	
	glcd_update_bbox(x, y, x+font_current.width,y+font_current.height);
	
}
