/*
 * graphics.c
 *
 * Created: 26/03/2012 11:10:51 PM
 *  Author: andy
 */ 

#include <stdlib.h>
#include "PCD8544.h"

extern uint8_t pcd8544_buffer[PCD8544_LCD_WIDTH * PCD8544_LCD_HEIGHT / 8];
extern PCD8544_BoundingBox_t pcd8544_bbox;
extern uint8_t *pcd8544_buffer_selected;
extern PCD8544_BoundingBox_t *pcd8544_bbox_selected;

void PCD8544_set_pixel(uint8_t x, uint8_t y, uint8_t color) {
	if (x > (PCD8544_LCD_WIDTH-1) || y > (PCD8544_LCD_HEIGHT-1))
		return;
	if (color) 
		pcd8544_buffer[x+ (y/8)*PCD8544_LCD_WIDTH] |= _BV(y%8);  
	else
		pcd8544_buffer[x+ (y/8)*PCD8544_LCD_WIDTH] &= ~_BV(y%8); 
	PCD8544_update_bbox(x,y,x,y);
}

uint8_t PCD8544_get_pixel(uint8_t x, uint8_t y) {
	if ((x >= PCD8544_LCD_WIDTH) || (y >= PCD8544_LCD_HEIGHT))
		return 0;
	
	return (pcd8544_buffer[x+ (y/8)*PCD8544_LCD_WIDTH] >> (7-(y%8))) & 0x1;  
}

// bresenham's algorithm
void PCD8544_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}
	
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	
	PCD8544_update_bbox( x0, y0, x1, y1 );
	
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
			PCD8544_set_pixel(y0, x0, color);
		} else {
			PCD8544_set_pixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void PCD8544_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	for (uint8_t i=x; i<x+w; i++) {
		for (uint8_t j=y; j<y+h; j++) {
			PCD8544_set_pixel(i, j, color);
		}
	}
	PCD8544_update_bbox(x, y, x+w, y+h);
}

void PCD8544_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
	for (uint8_t i=x; i<x+w; i++) {
		PCD8544_set_pixel(i, y, color);
		PCD8544_set_pixel(i, y+h-1, color);
	}
	for (uint8_t i=y; i<y+h; i++) {
		PCD8544_set_pixel(x, i, color);
		PCD8544_set_pixel(x+w-1, i, color);
	} 
	PCD8544_update_bbox(x, y, x+w, y+h);
}

void PCD8544_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
	PCD8544_update_bbox(x0-r, y0-r, x0+r, y0+r);
	
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	
	PCD8544_set_pixel(x0, y0+r, color);
	PCD8544_set_pixel(x0, y0-r, color);
	PCD8544_set_pixel(x0+r, y0, color);
	PCD8544_set_pixel(x0-r, y0, color);
	
	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		PCD8544_set_pixel(x0 + x, y0 + y, color);
		PCD8544_set_pixel(x0 - x, y0 + y, color);
		PCD8544_set_pixel(x0 + x, y0 - y, color);
		PCD8544_set_pixel(x0 - x, y0 - y, color);
		
		PCD8544_set_pixel(x0 + y, y0 + x, color);
		PCD8544_set_pixel(x0 - y, y0 + x, color);
		PCD8544_set_pixel(x0 + y, y0 - x, color);
		PCD8544_set_pixel(x0 - y, y0 - x, color);
		
	}
}

/* doesn't work when fill area is outside bounds of LCD, not sure why, need to fix! */
void PCD8544_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
	PCD8544_update_bbox(x0-r, y0-r, x0+r, y0+r);
	
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;
	
	for (uint8_t i=y0-r; i<=y0+r; i++) {
		PCD8544_set_pixel(x0, i, color);
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
		
		for (uint8_t i=y0-y; i<=y0+y; i++) {
			PCD8544_set_pixel(x0+x, i, color);
			PCD8544_set_pixel(x0-x, i, color);
		} 
		for (uint8_t i=y0-x; i<=y0+x; i++) {
			PCD8544_set_pixel(x0+y, i, color);
			PCD8544_set_pixel(x0-y, i, color);
		}    
	}
}