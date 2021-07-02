/**
   \file PIC18H.c
   \brief Functions relating to Microchip PIC18H (8-bit).
          For use with xc8 compiler.
					work
   \author Andy Gock (adapted by David Gautier from PIC24.c)
 */

/*
	Copyright (c) 2013, Andy Gock

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
#include "../glcd.h"


#if defined(GLCD_DEVICE_USER)
	#include "glcd_user_config.h"
	#include "glcd_user_config.c"
#else

#include "PIC18H.h"

#if defined(GLCD_DEVICE_PIC18H)

void glcd_init(void)
{

#if defined(GLCD_CONTROLLER_ST7565R)

	/* Set SS, DC and A0 pins as output */
	CONTROLLER_SS_TRIS = 0;
	CONTROLLER_A0_TRIS = 0;
	CONTROLLER_RST_TRIS = 0;

	/* Deselect LCD */

  GLCD_DESELECT();
	spi_master_open(CUSTOM0);

	/* Send reset pulse to LCD */
	glcd_reset();

	delay_ms(1);
	/* Begin sending data for initialisation sequence */
	glcd_ST7565R_init();
	/* Set all dots black and hold for 0.5s, then clear it, we do this so we can visually check init sequence is working */

  glcd_all_on();
	delay_ms(1000);
	glcd_normal();

	glcd_set_start_line(0);
	glcd_clear_now();

	glcd_select_screen(glcd_buffer,&glcd_bbox);
	glcd_clear();
	#elif defined(GLCD_CONTROLLER_SSD1309)
  /* Set SS, DC and A0 pins as output */
	#if defined(GLCD_CONTROLLER_SSD1309_SPI)

  CONTROLLER_SS_TRIS = 0;
	CONTROLLER_A0_TRIS = 0;
	CONTROLLER_RST_TRIS = 0;

	/* Deselect LCD */

  GLCD_DESELECT();
	spi_master_open(MASTER0);
	/* Send reset pulse to LCD */
	glcd_reset();
	delay_ms(1);
	/* Begin sending data for initialisation sequence */
	glcd_SSD1309_init();
	/* Set all dots black and hold for 0.5s, then clear it, we do this so we can visually check init sequence is working */
  glcd_set_start_line(0);

  glcd_all_on();
	delay_ms(250);
	glcd_normal();

	glcd_select_screen(glcd_buffer,&glcd_bbox);
  glcd_clear_now();
	glcd_clear();
  glcd_reset_bbox();


#else
  glcd_reset();
	delay_ms(1);
	glcd_SSD1309_init();
  glcd_normal();
  glcd_select_screen(glcd_buffer,&glcd_bbox);
  glcd_clear_now();
  glcd_reset_bbox();
#endif

#else
	#error "Controller not supported"
#endif /* GLCD_CONTROLLER_* */

}

void glcd_spi_write(uint8_t c)
{
  GLCD_SELECT();
	SPI_ExchangeByte(c);
	GLCD_DESELECT();
}

void glcd_reset(void)
{
	#if defined(GLCD_CONTROLLER_ST7565R)

    /* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	__delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();

  #elif defined(GLCD_CONTROLLER_SSD1309)
  GLCD_RESET_LOW();
	__delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
  #endif

}

#endif /* defined(GLCD_DEVICE_PIC18H) */

#endif /* GLCD_DEVICE_USER */
