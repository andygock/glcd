/**
 * \file unit_tests.c
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

#include <stdio.h>
#include <stdlib.h>
#include "glcd.h"
#include "unit_tests.h"

/** Fonts */
#include "fonts/font5x7.h"
//#include "fonts/Liberation_Sans11x14_Numbers.h"
#include "fonts/Liberation_Sans15x21_Numbers.h"
//#include "fonts/Liberation_Sans17x17_Alpha.h"
//#include "fonts/Liberation_Sans27x36_Numbers.h"
//#include "fonts/Bebas_Neue20x36_Bold_Numbers.h"

// Commercial fonts not included with distribution
//#include "library/glcd/fonts/HelveticaNeueLT_Com_57_Cn23x35_Numbers.h"
//#include "library/glcd/fonts/HelveticaNeueLT_Com_95_Blk18x19.h"

void glcd_test_circles(void)
{
	uint8_t x,y,radius;

	while (1) {
		uint8_t i;
		
		glcd_clear();

		// generate random(ish) position on display
		x = rand() % GLCD_LCD_WIDTH;
		y = rand() % GLCD_LCD_HEIGHT;
		radius = rand() % 50;

		//x = 70; y=25; radius=50; // for debugging

		// fill circle with black
		
		for (i=0; i<=radius; i++) {
			glcd_fill_circle(x,y,i,BLACK);
			glcd_write();
			_delay_ms(2);
		}

		// fill the same circle above but with white
		for (i=0; i<=radius; i++) {
			glcd_fill_circle(x,y,i,WHITE);
			glcd_write();
			_delay_ms(1);
		}
	}
}

void glcd_test_counter_and_graph(void)
{
	uint8_t count = 0;
	char string[8] = "";
	while(1) {
		glcd_clear_buffer();

		//glcd_tiny_set_font(Font5x7,5,7,32,127);
		//glcd_draw_string_xy(0,40,(char *)utoa(count,string,10));

		glcd_set_font(Liberation_Sans15x21_Numbers,15,21,46,57);
		//glcd_set_font(Liberation_Sans27x36_Numbers,27,36,46,57);
		//glcd_set_font(Bebas_Neue20x36_Bold_Numbers,20,36,46,57);
		//glcd_set_font(Bebas_Neue18x36_Numbers,18,36,46,57);
		//glcd_set_font(HelveticaNeueLT_Com_57_Cn23x35_Numbers,23,35,46,57); // commercial font - not for public distribution

		sprintf(string,"%d",count);
		glcd_draw_string_xy(0,0,string);
		glcd_bar_graph_horizontal(10,38,30,6,count*4);
		glcd_bar_graph_vertical(70,0,8,30,count*2);

		glcd_write();
		count += 1;

	}

}

void glcd_test_text_up_down(void)
{
	// moves some text up and down the display

	uint8_t y;
	uint8_t max_y;
	
	//glcd_set_font(Liberation_Sans11x14_Numbers,11,14,46,57);
	glcd_set_font(Liberation_Sans15x21_Numbers,15,21,46,57);
	//glcd_set_font(Liberation_Sans17x17_Alpha,17,17,46,90);

	max_y = GLCD_LCD_HEIGHT - font_current.height - 2; // max y start position for draw_string

	while(1) {
		// move top to bottom
		for (y=0; y<max_y; y++) {
			glcd_clear_buffer();
			glcd_draw_string_xy(0,y,"123");
			glcd_write();
			_delay_ms(80);
		}

		// move bottom to top
		for (y=(max_y); y>0; y--) {
			glcd_clear_buffer();
			glcd_draw_string_xy(0,y,"456");
			glcd_write();
			_delay_ms(80);
		}


	}

}

void glcd_test_tiny_text(void)
{
	char string[20] = "Hello World!";

	uint8_t c = 32;

	GLCD_TEXT_INIT();
	
	while(1) {
		// write chars to string from 32 to 127 ASCII
		uint8_t i;
		for (i=0; i<14; i++) {
			string[i] = c;
			c++;
			if (c > 127) {
				c = 32;
			}
		}

		// write null terminator
		string[14] = '\0';

		GLCD_WRITE(string);
		_delay_ms(1000);
	}

}

void glcd_test_hello_world(void)
{
	glcd_tiny_set_font(Font5x7,5,7,32,127);
	glcd_clear_buffer();
	glcd_tiny_draw_string(0,0,"Hello World!");
	glcd_write();
	while(1);
}
