/**
   \file glcd_graphics.h
   \brief Graphics routines
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

/** \addtogroup Graphics Graphics
 *  Graphics specific functions such as drawing lines, circles, rectangles etc.
 *  @{
 */

/**
 * Set pixel to specified colour
 * \param x X-coordinate
 * \param y Y-coordinate
 * \param color Colour to set pixel
 * \see ColourConstants
 */
void glcd_set_pixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * Get state of pixel from specified location
 * \param x X-coordinate
 * \param y Y-coordinate
 * \return Colour
 */
uint8_t glcd_get_pixel(uint8_t x, uint8_t y);

/**
 * Invert state of pixel of specified location
 * \param x X-coordinate
 * \param y Y-coordinate
 */
void glcd_invert_pixel(uint8_t x, uint8_t y);

/**
 * Draw line
 * \param x0 Start x-coordinate
 * \param y0 Start y-coordinate
 * \param x1 End x-coordinate
 * \param y1 End y-coordinate
 * \param color Colour to set pixels
 * \see ColourConstants
 */
void glcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

/**
 * Draw rectangle and fill with colour.
 * The border of the rectangle is the same as fill colour
 * \param x Start x-coordinate (left-most)
 * \param y Start y-coordinate (top-most)
 * \param w Width
 * \param h Height
 * \param color Colour to fill with
 * \see ColourConstants
 */
void glcd_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * Draw rectangle but do not fill.
 * The border of the rectangle is the same as fill colour
 * \param x Start x-coordinate (left-most)
 * \param y Start y-coordinate (top-most)
 * \param w Width
 * \param h Height
 * \param color Colour of border
 * \see ColourConstants
 */
void glcd_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * Draw rectangle but do not fill. User specified thickness.
 * The border of the rectangle is the same as fill colour
 * \param x Start x-coordinate (left-most)
 * \param y Start y-coordinate (top-most)
 * \param w Width (outermost pixels)
 * \param h Height
 * \param tx Thickness of horizontal border along X axis
 * \param ty Thickness of vertical border along Y axis
 * \param color Colour of border
 * \see ColourConstants
 */
void glcd_draw_rect_thick(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t tx, uint8_t ty, uint8_t color);

/**
 * Draw rectangle but do not fill. Place a shadow line on the bottom-right of the window.
 * The border of the rectangle is the same as fill colour
 * \param x Start x-coordinate (left-most)
 * \param y Start y-coordinate (top-most)
 * \param w Width
 * \param h Height
 * \param color Colour of border
 * \see ColourConstants
 */
void glcd_draw_rect_shadow(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * Draw circle but do not fill.
 * The border of the rectangle is the same as fill colour
 * \param x0 Centre x-coordinate (left-most)
 * \param y0 Centre y-coordinate (top-most)
 * \param r  Radius
 * \param color Colour of border
 * \see ColourConstants
 */
void glcd_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

/**
 * Draw circle and fill.
 * The border of the rectangle is the same as fill colour
 * \param x0 Centre x-coordinate (left-most)
 * \param y0 Centre y-coordinate (top-most)
 * \param r  Radius
 * \param color Colour of border
 * \see ColourConstants
 */
void glcd_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

/**
 * Invert pixels in a retangular area.
 * \param x Start x-coordinate (left-most)
 * \param y Start y-coordinate (top-most)
 * \param w Width
 * \param h Height 
 */
void glcd_invert_area(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

/**
 * Draw bitmap to screen buffer.
 * Note this will draw to the entire buffer, its not yet possible to draw partially to the LCD.
 * Not yet supported with AVR pgmspace.
 * \param data Pointer to bitmap data.
 */
void glcd_draw_bitmap(const unsigned char *data);

/** @}*/

#endif /* GLCD_GRAPHICS_H_ */
