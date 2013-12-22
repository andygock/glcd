/**
   \file glcd_text.h
   \brief GLCD Library - Text functions
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

#ifndef GLCD_TEXT_H
#define GLCD_TEXT_H

/** \addtogroup Text
 *  Functions relating to using text fonts.
 *  @{
 */

/** \addtogroup StandardText Standard Text
 *  Functions relating to using text fonts of all sizes.
 *  @{
 */
 
/** Set GLCD font to predefined font table. Only suitable for MikroElektronika font storage format.
 *
 *  \param font_table pointer to font table to be used
 *  \param width width of each character
 *  \param height height of each character
 *  \param start_char first character of font table
 *  \param end_char last character of font table
 *  \note Only suitable for MikroElektronika font storage format. For Stang format, use 
 *        glcd_tiny_set_font()
 *  \see glcd_tiny_set_font()
 */
#if defined(GLCD_DEVICE_AVR8)
void glcd_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char);
#else
void glcd_set_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char);
#endif

/** Set GLCD font to predefined font table. Suitable for different different types of font tables.
 *
 *  \param font_table pointer to font table to be used
 *  \param width width of each character
 *  \param height height of each character
 *  \param start_char first character of font table
 *  \param end_char last character of font table
 *	\param type font table type
 *  \note Only suitable for MikroElektronika font storage format. For Stang format, use 
 *        glcd_tiny_set_font()
 *  \see glcd_tiny_set_font()
 */
#if defined(GLCD_DEVICE_AVR8)
void glcd_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char, font_table_type_t type);
#else
void glcd_font(const char * font_table, uint8_t width, uint8_t height, char start_char, char end_char, font_table_type_t type);
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

#endif
