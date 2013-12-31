/**
 * \file LPC111x.c
 * \brief Initialisation and driver confiuration for NXP LPC111x ARM Cortex-M0 MCUs.
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

#include "../glcd.h"
#include "LPC111x.h"

#if defined(GLCD_DEVICE_LPC111X)

void glcd_init(void)
{

#if defined(GLCD_CONTROLLER_PCD8544)
	/*
	 * Set up SPI (SSP)
	 * Note: Max allowed SPI clock is 4 MHz from datasheet.
	 */

	/* Select SSP/SPI port */
	SSP_IOConfig( CONTROLLER_SPI_PORT_NUMBER );

	/* Initialise SSP/SPI port */
	SSP_Init( CONTROLLER_SPI_PORT_NUMBER );

	/* Above functions take care of SPI pins */

	/* Set SS, DC and RST pins to output */
	CONTROLLER_SS_PORT->DIR  |= (1 << CONTROLLER_SS_PIN);
	CONTROLLER_DC_PORT->DIR  |= (1 << CONTROLLER_DC_PIN);
	CONTROLLER_RST_PORT->DIR |= (1 << CONTROLLER_RST_PIN);

	/* Reset the display */
	glcd_reset();

	glcd_PCD8544_init();

	glcd_select_screen(glcd_buffer,&glcd_bbox);

	glcd_clear();

#else /* GLCD_CONTROLLER_PCD8544 */
	#error "Controller not supported by LPC111x"
#endif

}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SSP_Send(CONTROLLER_SPI_PORT_NUMBER,&c,1);
	GLCD_DESELECT();
}

void glcd_reset(void)
{
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}

#endif /* GLCD_DEVICE_LPC111x */
