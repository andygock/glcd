/**
   \file graphs.c
   \brief Functions relating to graphs. e.g bar graphs etc.
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
