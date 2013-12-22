/**
 * \file unit_tests.h
 * \brief Various test functions to demonstrate features of the library
 * \author Andy Gock
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

#ifndef _UNIT_TESTS_H
#define _UNIT_TESTS_H

#define GLCD_UNIT_TEST_BITMAP_ENABLE

extern volatile uint8_t unit_test_return;

/** Make random "exploding circles" */
void glcd_test_circles(void);

/* Shows a 8-bit counter incorementing, with a verticla and horizontal bar graph */
void glcd_test_counter_and_graph(void);

/* Shows a 16-bit counter incrementing, using glcdutils font format */
void glcd_test_glcdutils(void);

/** Scroll some text up and down the screen */
void glcd_test_text_up_down(void);

/** Display all chars of tiny 5x7 font, scrolling previous lines one by one every second */
void glcd_test_tiny_text(void);

/** Print hello world to display */
void glcd_test_hello_world(void);

/** Demonstrating rectangle drawing */
void glcd_test_rectangles(void);

/** Demonstrate scrolling bar graph */
void glcd_test_scrolling_graph(void);

/** Demonstrate bitmap display */
void glcd_test_bitmap_128x64(void);

#endif
