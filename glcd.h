/**
   \file glcd.h
   \brief GLCD Library main header file. This file must be included into project.
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

#ifndef _GLCD_H
#define _GLCD_H

#if defined(GLCD_DEVICE_AVR8)
	#include <avr/pgmspace.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>	
	#include "devices/AVR8.h"
#elif defined(GLCD_DEVICE_LPC111X)
	#include <LPC11xx.h>
	#include "devices/LPC111x.h"
	extern void delay_ms(uint32_t ms);
	#define PROGMEM
	#define _delay_ms(t) delay_ms(t)
#elif defined(GLCD_DEVICE_LPC11UXX)
	#include <LPC11Uxx.h>
	#include "devices/LPC11Uxx.h"
	extern void delay_ms(uint32_t ms);
	#define PROGMEM
	#define _delay_ms(t) delay_ms(t)	
#else
	#error "Device not supported"
#endif

#if defined(GLCD_CONTROLLER_PCD8544)
	#include "controllers/PCD8544.h"
#elif defined(GLCD_CONTROLLER_NT75451)
	#include "controllers/NT75451.h"	
#else
	#error "Controller not supported"
#endif

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#include <stdint.h>
#include "glcd_devices.h"
#include "glcd_controllers.h"
#include "glcd_graphics.h"
#include "unit_tests.h"

/**
 * \name Colour Constants
 * @{
 */
#define BLACK 1
#define WHITE 0
/**@}*/

/**
 * \name LCD Dimensions
 * @{
 */
#define GLCD_LCD_WIDTH 84
#define GLCD_LCD_HEIGHT 48
/**@}*/

/**
 * Bounding box for pixels that need to be updated
 */
typedef struct {
	uint8_t x_min;
	uint8_t y_min;
	uint8_t x_max;
	uint8_t y_max;
} glcd_BoundingBox_t;

/* Global variables used for GLCD library */
extern uint8_t glcd_buffer[GLCD_LCD_WIDTH * GLCD_LCD_HEIGHT / 8];
extern glcd_BoundingBox_t glcd_bbox;
extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;


/** \name Base Functions 
 *  @{
 */

void glcd_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax);
void glcd_reset_bbox(void);

/** Clear the display. This will clear the buffer and physically write and commit it to the LCD */
void glcd_clear(void);

/** Clear the display buffer only. This does not physically write the changes to the LCD */
void glcd_clear_buffer(void);
void glcd_select_screen(uint8_t *buffer, glcd_BoundingBox_t *bbox);
void glcd_scroll(int8_t x, int8_t y);
void glcd_scroll_line(void);

/** @}*/

enum font_table_type { STANG, MIKRO };

typedef struct {
	const char *font_table;
	uint8_t width;
	uint8_t height;
	char start_char;
	char end_char;
	enum font_table_type table_type;
} glcd_FontConfig_t;

extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;
extern glcd_FontConfig_t font_current;

/** \addtogroup Text
 *  Functions relating to using text fonts.
 *  @{
 */

/** \addtogroup TinyText Tiny Text
 *  Functions relating to using tiny 5x7 text fonts.
 *  @{
 */

/** Set font to be used from now on. This is the tiny 5x7 monospace font.
 *  \param font_table flash pointer to start from font table
 *  \param width      width of each character
 *  \param height     height of each character
 *  \param start_char start character
 *  \param end_char   end character
 */
void glcd_tiny_set_font(const char *font_table, uint8_t width, uint8_t height, char start_char, char end_char);

/** Write character to LCD in tiny 5x7 font.
 *  \param x    column position to start 
 *  \param line line number to be written (each line is 8 pixels high)
 *  \param c    char to be written
 */
void glcd_tiny_draw_char(uint8_t x, uint8_t line, char c);

/** Write string to display buffer in tiny 5x7 font.
 *  Will wrap to next line if needed. Screen is not updated. Use glcd_write() to physically update display.
 *  \param x    column position to start 
 *  \param line line number to be written (each line is 8 pixels high)
 *  \param str  string to be written
 */
void glcd_tiny_draw_string(uint8_t x, uint8_t line, char *str);

/** Write flash string to display buffer in tiny 5x7 font.
 *  Will wrap to next line if needed. Screen is not updated. Use glcd_write() to physically update display.
 *  \param x    column position to start 
 *  \param line line to be written (each line is 8 pixels high)
 *  \param str  string stored in flash memory to be written
 */
void glcd_tiny_draw_string_P(uint8_t x, uint8_t line, const char *str);

/** Write string to bottom row of display.
 *  Screen buffer is scrolled up by one line. Screen is then physically updated.
 *  \param str string to be written
 */
void glcd_tiny_draw_string_ammend(char *str);

/** Write string from flash memory to bottom row of display.
 *  Screen buffer is scrolled up by one line. Screen is then physically updated.
 *  \param str string to be written
 */
void glcd_tiny_draw_string_ammend_P(const char *str);

/** Initialise 5x7 text */
#define GLCD_TEXT_INIT()  glcd_tiny_set_font(Font5x7,5,7,32,127);

/** Write string to bottom-most line after scrolling everything else up */
#define GLCD_WRITE(str)   glcd_tiny_draw_string_ammend(str)

/** Write string from program memory to bottom-most line after scrolling everything else up */
#define GLCD_WRITE_P(str) glcd_tiny_draw_string_ammend_P(str)

/** @}*/

/** \addtogroup StandardText Standard Text
 *  Functions relating to using text fonts of all sizes.
 *  @{
 */
#if defined(GLCD_DEVICE_AVR8)
/** Set GLCD font to predefined font table
 *
 *  \param font_table pointer to font table to be used
 *  \param width width of each character
 *  \param height height of each character
 *  \param start_char first character of font table
 *  \param end_char last character of font table
 */
void glcd_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char);
#else
/** Set GLCD font to predefined font table
 *
 *  Note it is very important the arguments are set accurately, otherwise it will not work properly.
 *
 *  \param font_table pointer to font table to be used
 *  \param width width of each character
 *  \param height height of each character
 *  \param start_char first character of font table
 *  \param end_char last character of font table
 */
void glcd_set_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char);
#endif
/** Draw a char at specified location.
 *  \param x x location to place top-left of character frame
 *  \param y y location to place top-left of character frame
 *  \param c character to be drawn
 *  \return width of character, 0 on error (e.g could not read font table)
 */
uint8_t glcd_draw_char_xy(uint8_t x, uint8_t y, char c);

/** Draw a string at specified location.
 *  \param x x location to place top-left of character frame
 *  \param y y location to place top-left of character frame
 *  \param c pointer to string to be drawn
 */
void glcd_draw_string_xy(uint8_t x, uint8_t y, char *c);

/** Draw a string from program memory at specified location.
 *  \param x x location to place top-left of character frame
 *  \param y y location to place top-left of character frame
 *  \param str pointer to string in program memory to be drawn
 */
void glcd_draw_string_xy_P(uint8_t x, uint8_t y, const char *str);

/** @}*/

/** @}*/

/** \addtogroup Graphing
 *  Functions for graphing, e.g drawing bar graphs etc.
 *  @{
 */

/** Draw horizontal bar graph with 1 px wide border.
 *  The bar graph draws from left to right as val increases.
 *  \param x x location for top-left of border
 *  \param y y location for top-left of border
 *  \param width width of the border
 *  \param height height of the border (must be over 2)
 *  \param val value to display in graph (0-255 8 bit value).
 */
void glcd_bar_graph_horizontal(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val);

/** Draw horizontal bar graph with no border.
 *  The bar graph draws from left to right as val increases.
 *  \param x x location for top-left of bar
 *  \param y y location for top-left of bar
 *  \param width width of the bar at full val
 *  \param height height of the bar
 *  \param val value to display in graph (0-255 8 bit value).
 */
void glcd_bar_graph_horizontal_no_border(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val);

/** Draw vertical bar graph with 1px wide border.
 *  The bar graph draws from bottom to top as val increases.
 *  \param x x location for top-left of border
 *  \param y y location for top-left of border
 *  \param width width of the border
 *  \param height height of the border
 *  \param val value to display in graph (0-255 8 bit value).
 */ 
void glcd_bar_graph_vertical(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val);

/** Draw vertical bar graph with no border.
 *  The bar graph draws from bottom to top as val increases.
 *  \param x x location for top-left of bar
 *  \param y y location for top-left of bar
 *  \param width width of the bar
 *  \param height height of the bar
 *  \param val value to display in graph (0-255 8 bit value).
 */ 
void glcd_bar_graph_vertical_no_border(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val);

/** @}*/

#endif
