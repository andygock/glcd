/**
   \file glcd_graphics.h
   \brief 
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

#ifndef GLCD_GRAPHICS_H_
#define GLCD_GRAPHICS_H_

#if defined(GLCD_DEVICE_AVR8)
#include <avr/io.h>
#else

#endif

/** \addtogroup Graphics
 *  Graphics specific functions
 *  @{
 */

void glcd_set_pixel(uint8_t x, uint8_t y, uint8_t color);
uint8_t glcd_get_pixel(uint8_t x, uint8_t y);
void glcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void glcd_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void glcd_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void glcd_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
void glcd_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

/** @}*/

#endif /* GLCD_GRAPHICS_H_ */
