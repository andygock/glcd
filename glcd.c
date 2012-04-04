/**
    \file glcd.c
	\author Andy Gock
	\brief Basic GLCD functions affecting bounding box manipulation, clearing of screen and buffers, and basic scroll functions.
 */

#include <string.h>
#include <stdio.h>
#include "glcd.h"

// display buffer (e.g 504 bytes for 48x84 LCD)
uint8_t glcd_buffer[GLCD_LCD_WIDTH * GLCD_LCD_HEIGHT / 8];
glcd_BoundingBox_t glcd_bbox;

// pointers to buffer and bounding box for current screen being updated
uint8_t *glcd_buffer_selected;
glcd_BoundingBox_t *glcd_bbox_selected;

void glcd_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
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
	glcd_bbox_selected->x_min = GLCD_LCD_WIDTH - 1;
	glcd_bbox_selected->x_max = 0;
	glcd_bbox_selected->y_min = GLCD_LCD_HEIGHT -1;
	glcd_bbox_selected->y_max = 0;	
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
	for (uint8_t y=0; y<6; y++) {
		for (uint8_t x=0; x<84; x++) {
			
		}
	}
}

void glcd_scroll_line(void)
{
	for (uint8_t y=0; y<6; y++) {
		if (y <= 4) {
			// first 5 lines - banks 0 to 4
			memcpy(glcd_buffer_selected + y*84, glcd_buffer_selected + y*84 + 84, 84);
		} else {
			// last line - back 5 - clear it
			memset(glcd_buffer_selected + 5*84, 0x00, 84);
		}
	}
	glcd_update_bbox(0,0,GLCD_LCD_WIDTH - 1,GLCD_LCD_HEIGHT - 1);
}