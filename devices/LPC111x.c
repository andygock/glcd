/**
 *
 */

/*

	Copyright (c) 2012 Andy Gock

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#include "../glcd.h"
#include "LPC111x.h"

#if defined(GLCD_DEVICE_LPC111X)

// this needs to be defined elsewhere in the application
extern void delay_ms(uint32_t ms);

// make avr _delay_ms() compatible macro
#define _delay_ms(ms) delay_ms(ms);

void glcd_init(void)
{

#if defined(GLCD_CONTROLLER_PCD8544)
	// Set up SPI (SSP)
	// Note: Max allowed SPI clock is 4 MHz from datasheet.

	// select SSP/SPI port
	SSP_IOConfig( PCD8544_SPI_PORT_NUMBER );

	// initialise SSP/SPI port
	SSP_Init( PCD8544_SPI_PORT_NUMBER );

	// above functions take care of SPI pins

	// set SS, DC and RST pins to output
	PCD8544_SS_PORT->DIR  |= (1 << PCD8544_SS_PIN);
	PCD8544_DC_PORT->DIR  |= (1 << PCD8544_DC_PIN);
	PCD8544_RST_PORT->DIR |= (1 << PCD8544_RST_PIN);

	// deselect LCD
	//GLCD_DESELECT();

	// reset the display
	glcd_reset();

	// get into the EXTENDED mode!
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);

	// LCD bias select (4 is optimal?)
	glcd_command(PCD8544_SET_BIAS | 0x2);

	// set VOP
	glcd_command(PCD8544_SET_VOP | 50); // Experimentally determined

	// back to standard instructions
	glcd_command(PCD8544_FUNCTION_SET);

	// normal mode
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);

	glcd_select_screen((uint8_t *)&glcd_buffer,&glcd_bbox);

	glcd_clear();

#else /* GLCD_CONTROLLER_PCD8544 */
	#error Controller not supported.
#endif

}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SSP_Send(PCD8544_SPI_PORT_NUMBER,&c,1);
	GLCD_DESELECT();
}

void glcd_reset(void)
{
	// toggle RST low to reset. Minimum pulse 100ns on datasheet.
	GLCD_SELECT();
	GLCD_RESET_LOW();
	_delay_ms(1);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}

#endif /* GLCD_DEVICE_LPC111x */
