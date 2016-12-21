
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
	/* Supports variable width fonts */
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = MIKRO; /* Only supports MikroElektronika generated format at the moment */
}

#if defined(GLCD_DEVICE_AVR8)
void glcd_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char, font_table_type_t type)
#else
void glcd_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char, font_table_type_t type)
#endif
{
	/* Supports variable width fonts */
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = type; /* Only supports MikroElektronika generated format at the moment */
}

uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c)
{
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	
	if (font_current.table_type == STANG) {
		/* Font table in Pascal Stang format (single byte height with with no width specifier) */
		/* Maximum height of 8 bits only */
			
		uint8_t i;
		for ( i = 0; i < font_current.width; i++ ) {
#if defined(GLCD_DEVICE_AVR8)			
			uint8_t dat = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#else
			uint8_t dat = *( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
#endif
			uint8_t j;
			for (j = 0; j < 8; j++) {
				/* Set pixel color for each bit of the column (8-bits) */
				if (x+i >= GLCD_LCD_WIDTH || y+j >= GLCD_LCD_HEIGHT) {
					/* Don't try and write past the dimensions of the LCD */
					return 0;
				}
				if (dat & (1<<j)) {
					glcd_set_pixel(x+i,y+j,BLACK);
				} else {
					glcd_set_pixel(x+i,y+j,WHITE);
				}
			}
		}
		
		/* always return how many pixels of width were written */
		/* here for "stang" format fonts, it is always fixed */
		return font_current.width;
		
	} else if (font_current.table_type == MIKRO) {
		/* Font table in MikroElecktronica format
		   - multi row fonts allowed (more than 8 pixels high)
		   - variable width fonts allowed
		   a complete column is written before moving to the next */
		
		uint8_t i;
		uint8_t var_width;
		uint8_t bytes_high;
		uint8_t bytes_per_char;
		const char *p;
		
		if ((font_current.height % 8) > 0){
			bytes_high = (font_current.height / 8) + 1;
		}
		else{
			bytes_high = (font_current.height / 8);
		}
		bytes_per_char = font_current.width * bytes_high + 1; /* The +1 is the width byte at the start */
				
		p = font_current.font_table + (c - font_current.start_char) * bytes_per_char;

		/* The first byte per character is always the width of the character */
#if defined(GLCD_DEVICE_AVR8)		
		var_width = pgm_read_byte(p);
#else
		var_width = *p;
#endif
		p++; /* Step over the variable width field */

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
						/* Don't write past the dimensions of the LCD, skip the entire char */
						return 0;
					}
					
					/* We should not write if the y bit exceeds font height */
					if ((j*8 + bit) >= font_current.height) {
						/* Skip the bit */
						continue;
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
	
	} else if (font_current.table_type == GLCD_UTILS) {
		/* Font table format of glcd-utils
		   - A complete row is written first (not completed columns)
		   - Width not stored, but we can search and determine it
		   - Not yet supported */
		
		uint8_t var_width, n;
		uint8_t bytes_high, bytes_per_char;
		const char *p;
		uint8_t j;
		
		bytes_high = font_current.height / 8 + 1;
		bytes_per_char = font_current.width * bytes_high;
		
		/* Point to chars first byte */
		p = font_current.font_table + (c - font_current.start_char) * bytes_per_char;

		/* Determine the width of the character */
		var_width = font_current.width;
		
		n = 0; /* How many columns back from the end */
		
		while (1) {
			uint8_t max_byte = 0;
			uint8_t row = 0;
			
			for (row = 0; row < bytes_high; row++) {
				uint8_t offset;
				offset = (font_current.width - 1 - n) * row;
				max_byte = *(p + offset);
			}
			if (max_byte == 0) {
				/* column is empty for all rows, go left and test again */
				/* reduce variable width by 1 */
				var_width--;
				if (var_width == 0) {
					break;
				}
			} else {
				break; /* Part of a character was found */
			}
			n++;
		}
		
		/* Uncomment line below, to force fixed width, for debugging only */
		//var_width = font_current.width; // bypass auto width detection, treat as fixed width
				
		/* For glcd-utils format, we write one complete row at a time */
		 /* loop as rows, 1st row, j=0 */
		for ( j = 0; j < bytes_high; j++ ) {
			/* Loop one row at a time */
		
			uint8_t i;
			for ( i = 0; i < var_width; i++ ) {
				/* Loop one column at a time */
				
				uint8_t dat, bit;
				
#if defined(GLCD_DEVICE_AVR8)
				dat = pgm_read_byte( p + j*font_current.width + i );
#else
				dat = *( p + j*font_current.width + i );
#endif
				
				for (bit = 0; bit < 8; bit++) {
					
					if ((x+i) >= GLCD_LCD_WIDTH || (y+j*8+bit) >= GLCD_LCD_HEIGHT) {
						/* Don't write past the dimensions of the LCD, skip the entire char */
						return 0;
					}
					
					/* We should not write if the y bit exceeds font height */
					if ((j*8 + bit) >= font_current.height) {
						/* Skip the bit */
						continue;
					}
					
					if (dat & (1<<bit)) {
						glcd_set_pixel(x+i,y+j*8+bit,BLACK);
					} else {
						glcd_set_pixel(x+i,y+j*8+bit,WHITE);
					}
				}									
			} /* i */
		} /* j */
		
		return var_width; /* Number of columns written to display */
		
	} else {
		/* Don't recognise the font table */
		return 0;
		
	}

}

void glcd_draw_string_xy(uint8_t x, uint8_t y, char *c)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		/* Character won't fit */
		return;
	}

	while (*c) {
		width = glcd_draw_char_xy(x,y,*c);
		x += (width + 1);
		c++;
	}		
}

void glcd_draw_string_xy_P(uint8_t x, uint8_t y, const char *str)
{
	uint8_t width;

	if (y > (GLCD_LCD_HEIGHT - font_current.height - 1)) {
		/* Character won't fit */
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
		c++;
	}		
}

