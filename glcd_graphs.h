/**
   \file glcd_graphs.h
   \brief GLCD Library - Graph drawing functions.
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

#ifndef GLCD_GRAPHS_H
#define GLCD_GRAPHS_H

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

/** \todo write doc */
void glcd_scrolling_bar_graph(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t val);

/** @}*/

#endif
