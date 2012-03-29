/*
 * text.c
 *
 * Created: 28/03/2012 1:54:01 AM
 *  Author: andy
 */ 

#include <avr/pgmspace.h>
#include "PCD8544.h"

extern uint8_t *pcd8544_buffer_selected;
extern PCD8544_BoundingBox_t *pcd8544_bbox_selected;

PCD8544_FontConfig_t font_current;

void PCD8544_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char)
{
	// supports variable width fonts
	font_current.font_table = font_table;
	font_current.width = width;
	font_current.height = height;
	font_current.start_char = start_char;
	font_current.end_char = end_char;
	font_current.table_type = MIKRO;
}

uint8_t PCD8544_draw_char_xy(uint8_t x, uint8_t y, char c)
{
	if (c < font_current.start_char || c > font_current.end_char) {
		c = '.';
	}
	
	if (font_current.table_type == STANG) {
		// font table in Pascal Stang format (single byte height with with no width specifier


			
		for ( uint8_t i = 0; i < font_current.width; i++ ) {
			uint8_t dat = pgm_read_byte( font_current.font_table + ((c - font_current.start_char) * (font_current.width)) + i );
			for (uint8_t j = 0; j < 8; j++) {
				if (x+i >= PCD8544_LCD_WIDTH || y+j >= PCD8544_LCD_HEIGHT) {
					return 0;
				}					
				if (dat & (1<<j)) {
					PCD8544_set_pixel(x+i,y+j,BLACK);
				} else {
					PCD8544_set_pixel(x+i,y+j,WHITE);
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
		if (x+var_width >= PCD8544_LCD_WIDTH || y+font_current.height >= PCD8544_LCD_HEIGHT) {
			return;
		}
		*/

		for ( uint8_t i = 0; i < var_width; i++ ) {
			for ( uint8_t j = 0; j < bytes_high; j++ ) {
				uint8_t dat = pgm_read_byte( p + i*bytes_high + j );
				for (uint8_t bit = 0; bit < 8; bit++) {
					
					if (x+i >= PCD8544_LCD_WIDTH || y+j*8+bit >= PCD8544_LCD_HEIGHT) {
						return 0;
					}					
					
					if (dat & (1<<bit)) {
						PCD8544_set_pixel(x+i,y+j*8+bit,BLACK);
					} else {
						PCD8544_set_pixel(x+i,y+j*8+bit,WHITE);
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

void PCD8544_draw_string_xy(uint8_t x, uint8_t y, char *c)
{
	uint8_t width;
	while (*c) {
		width = PCD8544_draw_char_xy(x,y,*c);
		x += (width + 1);
		//if (x+width >= PCD8544_LCD_WIDTH) {
		//	return;
		//}
		c++;
	}		
}

void PCD8544_draw_string_xy_P(uint8_t x, uint8_t y, const char *str)
{
	uint8_t width;
	while (1) {
		char c = pgm_read_byte(str++);
		if (!c)
			return;
					
		width = PCD8544_draw_char_xy(x,y,c);
		x += (width + 1);
		//if (x+width >= PCD8544_LCD_WIDTH) {
		//	return;
		//}		
		c++;
	}		
}

