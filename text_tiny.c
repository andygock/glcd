/**
   \file text_tiny.c
   \brief Functions relating to using tiny 5x7 text fonts.
   \author Andy Gock
 */ 

#include "glcd.h"

extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;
extern glcd_FontConfig_t font_current;

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
	// only works for fonts < 8 bits in height
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
	
	for ( uint8_t i = 0; i < font_current.width; i++ ) {
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
			x = 0;    // ran out of this line
			line++;
		}
		if (line >= (GLCD_LCD_HEIGHT/(font_current.height + 1)))
			return;        // ran out of space :(
	}
}

void glcd_tiny_draw_string_P(uint8_t x, uint8_t line, const char *str)
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
			x = 0;    // ran out of this line
			line++;
		}
		if (line >= (GLCD_LCD_HEIGHT/(font_current.height + 1)))
			return;        // ran out of space :(
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
