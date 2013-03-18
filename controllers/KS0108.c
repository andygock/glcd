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

#if defined(GLCD_CONTROLLER_KS0108)

#include "../glcd.h"
#include "KS0108.h"

void glcd_command(uint8_t c)
{
	/* Set up RS and RW */
	GLCD_RS_LOW();
	GLCD_RW_LOW();
	
	/* Put the data on the bus */
	glcd_parallel_write(c);
}

void glcd_data(uint8_t c)
{
	/* Set up RS and RW */
	GLCD_RS_HIGH();
	GLCD_RW_LOW();
	
	/* Put the data on the bus */
	glcd_parallel_write(c);

}

void glcd_set_x_address(uint8_t x)
{
	/* x must be between from 0 to 127 */
	/* Datasheet calls this "y", but we call x for HORIZONTAL
	   direction */

	if (x < 64) {
		/* Page 1 - set CS2 high */
		
		GLCD_PAGE_1();
		glcd_command( 0b01000000 | (0b00111111 & x) );
		
	} else if ((x >= 64) && (x < 127)) {
		/* Page 2 - set CS1 high */
		
		GLCD_PAGE_2();
		glcd_command( 0b01000000 | (0b00111111 & (x-64)) );
		
	} else {
		/* Page exceeds allowed limit, do nothing */
	}
	
}

void glcd_set_y_address(uint8_t y)
{
	/* Set "page" (also known as a "bank"), this is not a pixel offset! */
	/* Datasheet calls this "x", but we call y for VERTICAL
	   direction */
	/* y must be from 0 to 7 */
	
	glcd_command( 0b10111000 | (0b111 & y) );

}


void glcd_write()
{
	
}	

#endif /* defined(GLCD_CONTROLLER_KS0108) */