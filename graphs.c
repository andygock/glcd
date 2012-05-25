/**
   \file graphs.c
   \brief Functions relating to graphs. e.g bar graphs etc.
   \author Andy Gock
 */ 

#include "glcd.h"

static uint8_t glcd_map(uint8_t x1, uint8_t x2, uint8_t x);

void glcd_bar_graph_horizontal(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val)
{
	if (height < 3) {
		return;
	}
	glcd_draw_rect(x, y, width, height, BLACK);
	glcd_fill_rect(x+1, y+1, glcd_map(0,width-2,val), height-2 , BLACK);
}

void glcd_bar_graph_horizontal_no_border(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val)
{
	if (height < 3) {
		return;
	}	
	glcd_fill_rect(x, y, glcd_map(0,width,val), height , BLACK);
}

void glcd_bar_graph_vertical(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val)
{
	glcd_draw_rect(x, y, width, height, BLACK);
	glcd_fill_rect(x+1, y+1+glcd_map(0,height-2,255-val), width-2, height-2-glcd_map(0,height-2,255-val), BLACK);
}

void glcd_bar_graph_vertical_no_border(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val)
{
	glcd_fill_rect(x, y+glcd_map(0,height-2,255-val), width, height-2-glcd_map(0,height-2,255-val), BLACK);
}

static uint8_t glcd_map(uint8_t x1, uint8_t x2, uint8_t x)
{
	return x1+(x2-x1)*x/255;	
}