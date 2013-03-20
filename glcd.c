/**
	\file glcd.c
	\author Andy Gock
	\brief Basic GLCD functions affecting bounding box manipulation,
	       clearing of screen and buffers, and basic scroll functions.
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

#include <string.h>
#include <stdio.h>
#include "glcd.h"

/** \addtogroup GlobalVars Global Variables
 *  @{
 */

/**
 *  Screen buffer
 *
 *  Requires at least one bit for every pixel (e.g 504 bytes for 48x84 LCD)
 */
uint8_t glcd_buffer[GLCD_LCD_WIDTH * GLCD_LCD_HEIGHT / 8];

/**
 * Keeps track of bounding box of area on LCD which need to be
 * updated next reresh cycle
 */
glcd_BoundingBox_t glcd_bbox;

/**
 * Pointer to screen buffer currently in use.
 */
uint8_t *glcd_buffer_selected;

/**
 * Pointer to bounding box currently in use.
 */
glcd_BoundingBox_t *glcd_bbox_selected;

/** @} */

void glcd_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
	/* Keep and check bounding box within limits of LCD screen dimensions */
	if (xmin > (GLCD_LCD_WIDTH-1)) {
		xmin = GLCD_LCD_WIDTH-1;
	}
	if (xmax > (GLCD_LCD_WIDTH-1)) {
		xmax = GLCD_LCD_WIDTH-1;
	}

	if (ymin > (GLCD_LCD_HEIGHT-1)) {
		ymin = GLCD_LCD_HEIGHT-1;
	}
	if (ymax > (GLCD_LCD_HEIGHT-1)) {
		ymax = GLCD_LCD_HEIGHT-1;
	}

	/* Update the bounding box size */
	if (xmin < glcd_bbox_selected->x_min) {
		glcd_bbox_selected->x_min = xmin;
	}		
	if (xmax > glcd_bbox_selected->x_max) {
		glcd_bbox_selected->x_max = xmax;
	}
	if (ymin < glcd_bbox_selected->y_min) {
		glcd_bbox_selected->y_min = ymin;
	}		
	if (ymax > glcd_bbox_selected->y_max) {
		glcd_bbox_selected->y_max = ymax;
	}			
}

void glcd_reset_bbox()
{
	/* Used after physically writing to the LCD */
	glcd_bbox_selected->x_min = GLCD_LCD_WIDTH - 1;
	glcd_bbox_selected->x_max = 0;
	glcd_bbox_selected->y_min = GLCD_LCD_HEIGHT -1;
	glcd_bbox_selected->y_max = 0;	
}

void glcd_bbox_reset() {
	glcd_reset_bbox();
}

void glcd_bbox_refresh() {
	/* Marks bounding box as entire screen, so on next glcd_write(), it writes the entire buffer to the LCD */
	glcd_bbox_selected->x_min = 0;
	glcd_bbox_selected->x_max = GLCD_LCD_WIDTH - 1;
	glcd_bbox_selected->y_min = 0;
	glcd_bbox_selected->y_max = GLCD_LCD_HEIGHT -1;		
}

void glcd_clear(void) {
	memset(glcd_buffer_selected, 0x00, GLCD_LCD_WIDTH * GLCD_LCD_HEIGHT / 8);
	glcd_update_bbox(0,0,GLCD_LCD_WIDTH - 1,GLCD_LCD_HEIGHT - 1);
	glcd_write();
}

void glcd_clear_buffer(void) {
	memset(glcd_buffer_selected, 0x00, GLCD_LCD_WIDTH * GLCD_LCD_HEIGHT / 8);
	glcd_update_bbox(0,0,GLCD_LCD_WIDTH - 1,GLCD_LCD_HEIGHT - 1);
}

void glcd_select_screen(uint8_t *buffer, glcd_BoundingBox_t *bbox)
{
	glcd_buffer_selected = buffer;
	glcd_bbox_selected = bbox;
}

void glcd_scroll(int8_t x, int8_t y)
{
	/** \todo Skeleton */
	
	uint8_t row;
	
	for (row=0; row<(GLCD_LCD_HEIGHT / 8); row++) {
		uint8_t x;
		for (x=0; x<GLCD_LCD_WIDTH; x++) {
			
		}
	}
}

void glcd_scroll_line(void)
{
	uint8_t y;
	uint8_t number_of_rows = GLCD_LCD_HEIGHT / 8;
	for (y=0; y<number_of_rows; y++) {
		if (y < (number_of_rows - 1)) {
			/* All lines except the last */
			memcpy(glcd_buffer_selected + y*GLCD_LCD_WIDTH, glcd_buffer_selected + y*GLCD_LCD_WIDTH + GLCD_LCD_WIDTH, GLCD_LCD_WIDTH);
		} else {
			/* Last line, clear it */
			memset(glcd_buffer_selected + (number_of_rows - 1)*GLCD_LCD_WIDTH, 0x00, GLCD_LCD_WIDTH);
		}
	}
	glcd_update_bbox(0,0,GLCD_LCD_WIDTH - 1,GLCD_LCD_HEIGHT - 1);
}

