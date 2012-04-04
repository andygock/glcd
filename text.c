/**
   \file text.c
   \brief Functions relating to using text fonts of all sizes.
   \author Andy Gock
 */ 

#include <avr/pgmspace.h>
#include "glcd.h"

extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;

glcd_FontConfig_t font_current;

void glcd_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char)
{
	// supports variable width fonts
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = MIKRO;
}

uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c)
{
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	
	if (font_current.table_type == STANG) {
		// font table in Pascal Stang format (single byte height with with no width specifier
			
		for ( uint8_t i = 0; i < font_current.width; i++ ) {
			uint8_t dat = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
			for (uint8_t j = 0; j < 8; j++) {
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

		uint8_t bytes_high = font_current.height / 8 + 1;
		uint8_t bytes_per_char = font_current.width * bytes_high + 1;
		const char *p;
		p = font_current.font_table + (c - font_current.start_char) * bytes_per_char;
		
		uint8_t var_width = pgm_read_byte(p);
		p++; // step over the variable width field

		/*
		if (x+var_width >= GLCD_LCD_WIDTH || y+font_current.height >= GLCD_LCD_HEIGHT) {
			return;
		}
		*/

		for ( uint8_t i = 0; i < var_width; i++ ) {
			for ( uint8_t j = 0; j < bytes_high; j++ ) {
				uint8_t dat = pgm_read_byte( p + i*bytes_high + j );
				for (uint8_t bit = 0; bit < 8; bit++) {
					
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
	while (*c) {
		width = glcd_draw_char_xy(x,y,*c);
		x += (width + 1);
		//if (x+width >= GLCD_LCD_WIDTH) {
		//	return;
		//}
		c++;
	}		
}

void glcd_draw_string_xy_P(uint8_t x, uint8_t y, const char *str)
{
	uint8_t width;
	while (1) {
		char c = pgm_read_byte(str++);
		if (!c)
			return;
					
		width = glcd_draw_char_xy(x,y,c);
		x += (width + 1);
		//if (x+width >= GLCD_LCD_WIDTH) {
		//	return;
		//}		
		c++;
	}		
}

