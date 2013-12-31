/**
	\file LPC11Uxx.c
	\author Andy Gock
	\brief Functions specific to LPC11Uxx devices.
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
#include "LPC11Uxx.h"

#if defined(GLCD_DEVICE_LPC11UXX)

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

	/* Deselect LCD */
	GLCD_DESELECT();

	glcd_PCD8544_init();

	glcd_select_screen(glcd_buffer,&glcd_bbox);

	glcd_clear();

#elif defined(GLCD_CONTROLLER_NT75451)
	/* Parallel interface controller used on NGX BlueBoards */
	
	/* Set 4x control lines pins as output */
	LPC_GPIO->DIR[CONTROLLER_LCD_EN_PORT] |= (1U<<CONTROLLER_LCD_EN_PIN);
	LPC_GPIO->DIR[CONTROLLER_LCD_RW_PORT] |= (1U<<CONTROLLER_LCD_RW_PIN);
	LPC_GPIO->DIR[CONTROLLER_LCD_RS_PORT] |= (1U<<CONTROLLER_LCD_RS_PIN);
	LPC_GPIO->DIR[CONTROLLER_LCD_CS_PORT] |= (1U<<CONTROLLER_LCD_CS_PIN);
	
	/* Don't worry about setting default RS/RW/CS/EN, they get set during use */
	
#ifdef CONTROLLER_LCD_DATA_PORT	
	/* Set data pins as output */
	LPC_GPIO->DIR[CONTROLLER_LCD_D0_PORT] |= GLCD_PARALLEL_MASK;
#else
	#error "Support of parallel data pins on different ports not supported."
#endif

	glcd_NT75451_init();

	/* Select default screen buffer */
	glcd_select_screen(glcd_buffer,&glcd_bbox);

	/* Clear the screen buffer */
	glcd_clear();
	
#else /* GLCD_CONTROLLER_PCD8544 */
	#error "Controller not supported by LPC111x"
#endif

}

#if defined(GLCD_USE_PARALLEL)

/** Write byte via parallel interface */
void glcd_parallel_write(uint8_t c)
{
	
	uint32_t port_output = \
		( ( (1U << 0) & c ? 1 : 0 ) << CONTROLLER_LCD_D0_PIN ) | \
		( ( (1U << 1) & c ? 1 : 0 ) << CONTROLLER_LCD_D1_PIN ) | \
		( ( (1U << 2) & c ? 1 : 0 ) << CONTROLLER_LCD_D2_PIN ) | \
		( ( (1U << 3) & c ? 1 : 0 ) << CONTROLLER_LCD_D3_PIN ) | \
		( ( (1U << 4) & c ? 1 : 0 ) << CONTROLLER_LCD_D4_PIN ) | \
		( ( (1U << 5) & c ? 1 : 0 ) << CONTROLLER_LCD_D5_PIN ) | \
		( ( (1U << 6) & c ? 1 : 0 ) << CONTROLLER_LCD_D6_PIN ) | \
		( ( (1U << 7) & c ? 1 : 0 ) << CONTROLLER_LCD_D7_PIN );

	/* Perform the write */

	/* Clear data bits to zero and set required bits as needed */
	LPC_GPIO->CLR[CONTROLLER_LCD_D0_PORT] |= GLCD_PARALLEL_MASK;
	LPC_GPIO->SET[CONTROLLER_LCD_D0_PORT] |= port_output;
	
	GLCD_RW_LOW();
	GLCD_CS_LOW();
	GLCD_EN_HIGH();
	
	/* Must hold for minimum 80 ns = ~12.5 MHz pulse */
	
	/* Do whatever is needed for your MCU */
	//glcd_delay(1);
	
	GLCD_EN_LOW();
	GLCD_CS_HIGH();
	GLCD_RW_HIGH();
	
}

#else

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SSP_Send(CONTROLLER_SPI_PORT_NUMBER,&c,1);
	GLCD_DESELECT();
}

#endif /* GLCD_USE_PARALLEL */

void glcd_reset(void)
{
#if defined(GLCD_CONTROLLER_PCD8544)
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
	
#elif defined(GLCD_CONTROLLER_NT75451)
	/* No firmware reset possible with our test board (BlueBoard) */
	
#endif /* GLCD_CONTROLLER_PCD8544 */	
}

void glcd_delay(uint32_t count)
{
  uint16_t j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}

#endif /* GLCD_DEVICE_LPC11UXX */
