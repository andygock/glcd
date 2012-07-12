/**
   \file text.c
   \brief Functions relating to using text fonts of all sizes.
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

extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;

glcd_FontConfig_t font_current;

#if defined(GLCD_DEVICE_AVR8)
void glcd_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char)
#else
void glcd_set_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char)
#endif
{
	// supports variable width fonts
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = MIKRO; // only supports MikroElektronika generated format
}

uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c)
{
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	
	if (font_current.table_type == STANG) {
		// font table in Pascal Stang format (single byte height with with no width specifier
			
		uint8_t i;
		for ( i = 0; i < font_current.width; i++ ) {
#if defined(GLCD_DEVICE_AVR8)			
			uint8_t dat = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#else
			uint8_t dat = *( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#endif
			uint8_t j;
			for (j = 0; j < 8; j++) {
				if (x+i >= GLCD_LCD_WIDTH || y+j >= GLCD_LCD_HEIGHT) {
					return 0;
				}					
				if (dat & (1<<j)) {
					glcd_set_pixel(x+i,y+j,BLACK);
				} else {
					glcd_set_pixel(x+i,y+j,WHITE);
				}
			}
		}
		return font_current.width;
		
	} else if (font_current.table_type == MIKRO) {
		// font table in MikroElecktronica format

		uint8_t i;
		uint8_t var_width;
		
		uint8_t bytes_high = font_current.height / 8 + 1;
		uint8_t bytes_per_char = font_current.width * bytes_high + 1;
		
		const char *p;
		p = font_current.font_table + (c - font_current.start_char) * bytes_per_char;

#if defined(GLCD_DEVICE_AVR8)		
		var_width = pgm_read_byte(p);
#else
		var_width = *p;
#endif
		p++; // step over the variable width field

		/*
		if (x+var_width >= GLCD_LCD_WIDTH || y+font_current.height >= GLCD_LCD_HEIGHT) {
			return;
		}
		*/

		
		for ( i = 0; i < var_width; i++ ) {
			uint8_t j;
			for ( j = 0; j < bytes_high; j++ ) {
#if defined(GLCD_DEVICE_AVR8)				
				uint8_t dat = pgm_read_byte( p + i*bytes_high + j );
#else
				uint8_t dat = *( p + i*bytes_high + j );
#endif
				uint8_t bit;
				for (bit = 0; bit < 8; bit++) {
					
					if (x+i >= GLCD_LCD_WIDTH || y+j*8+bit >= GLCD_LCD_HEIGHT) {
						return 0;
					}					
					
					if (dat & (1<<bit)) {
						glcd_set_pixel(x+i,y+j*8+bit,BLACK);
					} else {
						glcd_set_pixel(x+i,y+j*8+bit,WHITE);
					}
				}									
			}				
		}
		return var_width;	
		
	} else {
		// don't recognise the font table
		return 0;
	}

}

void glcd_draw_string_xy(uint8_t x, uint8_t y, char *c)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		// character won't fit
		return;
	}

	while (*c) {
		width = glcd_draw_char_xy(x,y,*c);
		x += (width + 1);
		// ignore section - up to user to make sure text does not overflow display width
		//if (x+width >= GLCD_LCD_WIDTH) {
		//	return;
		//}
		c++;
	}		
}

void glcd_draw_string_xy_P(uint8_t x, uint8_t y, const char *str)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		// character won't fit
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
					
		width = glcd_draw_char_xy(x,y,c);
		x += (width + 1);
		// ignore section - up to user to make sure text does not overflow display width
		//if (x+width >= GLCD_LCD_WIDTH) {
		//	return;
		//}		
		c++;
	}		
}

