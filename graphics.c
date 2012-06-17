/**
   \file graphics.c
   \brief Functions relating to graphics. e.g drawing lines, rectangles, circles etc.
   \author Andy Gock

   Some functions based on Limor Fried's PCD8544 Arduino library.

 */ 

/*
	Copyright (c) 2012, Andy Gock

	Copyright (c) 2012, Adafruit Industries

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of the copyright holders nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdlib.h>
#include "glcd.h"

// based on PCD8544 library by Limor Fried
void glcd_set_pixel(uint8_t x, uint8_t y, uint8_t color) {
	if (x > (GLCD_LCD_WIDTH-1) || y > (GLCD_LCD_HEIGHT-1)) {
		// don't do anything if x/y is outside bounds of display size
		return;
	}

	if (color) {
		// set black
		glcd_buffer[x+ (y/8)*GLCD_LCD_WIDTH] |= ( 1<< (y%8));
	} else {
		// set white
		glcd_buffer[x+ (y/8)*GLCD_LCD_WIDTH] &= ~ (1<< (y%8));
	}

	glcd_update_bbox(x,y,x,y);
}

// based on PCD8544 library by Limor Fried
uint8_t glcd_get_pixel(uint8_t x, uint8_t y) {
	if ((x >= GLCD_LCD_WIDTH) || (y >= GLCD_LCD_HEIGHT))
		return 0;
	
	return (glcd_buffer[x+ (y/8)*GLCD_LCD_WIDTH] >> (7-(y%8))) & 0x1;  
}

// bresenham's algorithm - based on PCD8544 library Limor Fried
void glcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}
	
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	
	glcd_update_bbox( x0, y0, x1, y1 );
	
	uint8_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);
	
	int8_t err = dx / 2;
	int8_t ystep;
	
	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}
	
	for (; x0<=x1; x0++) {
		if (steep) {
			glcd_set_pixel(y0, x0, color);
		} else {
			glcd_set_pixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void glcd_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	for (int16_t i=x; i<x+w; i++) {
		for (int16_t j=y; j<y+h; j++) {
			glcd_set_pixel(i, j, color);
		}
	}
	glcd_update_bbox(x, y, x+w-1, y+h-1);
}

void glcd_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	for (int16_t i=x; i<x+w; i++) {
		glcd_set_pixel(i, y, color);
		glcd_set_pixel(i, y+h-1, color);
	}
	for (int16_t i=y; i<y+h; i++) {
		glcd_set_pixel(x, i, color);
		glcd_set_pixel(x+w-1, i, color);
	} 
	glcd_update_bbox(x, y, x+w-1, y+h-1);
}

void glcd_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
	glcd_update_bbox(x0-r, y0-r, x0+r, y0+r);
	
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	
	glcd_set_pixel(x0, y0+r, color);
	glcd_set_pixel(x0, y0-r, color);
	glcd_set_pixel(x0+r, y0, color);
	glcd_set_pixel(x0-r, y0, color);
	
	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		glcd_set_pixel(x0 + x, y0 + y, color);
		glcd_set_pixel(x0 - x, y0 + y, color);
		glcd_set_pixel(x0 + x, y0 - y, color);
		glcd_set_pixel(x0 - x, y0 - y, color);
		
		glcd_set_pixel(x0 + y, y0 + x, color);
		glcd_set_pixel(x0 - y, y0 + x, color);
		glcd_set_pixel(x0 + y, y0 - x, color);
		glcd_set_pixel(x0 - y, y0 - x, color);
		
	}
}

void glcd_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
	glcd_update_bbox(x0-r, y0-r, x0+r, y0+r);
	
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	
	for (int16_t i=y0-r; i<=y0+r; i++) {
		glcd_set_pixel(x0, i, color);
	}
	
	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		for (int16_t i=y0-y; i<=y0+y; i++) {
			glcd_set_pixel(x0+x, i, color);
			glcd_set_pixel(x0-x, i, color);
		} 
		for (int16_t i=y0-x; i<=y0+x; i++) {
			glcd_set_pixel(x0+y, i, color);
			glcd_set_pixel(x0-y, i, color);
		}    
	}
}
