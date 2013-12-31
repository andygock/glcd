/**
   \file AVR8.c
   \brief Functions relating to Atmel AVR 8-bit AVRs.
          For use with GNU toolchain
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

#include "../glcd.h"

#if defined(GLCD_DEVICE_AVR8)

void glcd_init(void)
{
	
#if defined(GLCD_CONTROLLER_PCD8544)

	/* Set pin directions */
	
	/*
	 * Set up SPI for AVR8
	 * Note: AVR's SS pin must be set to output, regardless of whether we
	 * actually use it. This is a requirement of SPI mster mode.
	 */
	sbi(DDR(AVR_SS_PORT),AVR_SS_PIN);
	
	/*
	 *  Set MOSI, Master SS, SCK to output (otherwise SPI won't work)
	 *  Must be done even if native SS pin not used
	 */
	sbi(DDR(CONTROLLER_MOSI_PORT),CONTROLLER_MOSI_PIN);
	sbi(DDR(CONTROLLER_SS_PORT),CONTROLLER_SS_PIN);
	sbi(DDR(CONTROLLER_SCK_PORT),CONTROLLER_SCK_PIN);
		
	/* Set SS, DC and RST pins to output */
	sbi( DDR(CONTROLLER_SS_PORT), CONTROLLER_SS_PIN );
	sbi( DDR(CONTROLLER_DC_PORT), CONTROLLER_DC_PIN );
	sbi( DDR(CONTROLLER_RST_PORT), CONTROLLER_RST_PIN );
	
	/* Deselect LCD */
	GLCD_DESELECT();

	/*
	 * Max allowed SPI clock is 4 MHz from datasheet.
	 * Enable SPI, set master mode and clock rate to /4 (4MHz with F_CPU=8MHz)
	 */
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR = 0;
	
	glcd_PCD8544_init();

	/* Select screen buffer */
	glcd_select_screen(glcd_buffer,&glcd_bbox);
	
	/* Clear screen, we are now ready to go */
	glcd_clear();

#elif defined(GLCD_CONTROLLER_ST7565R)

	/* Set up GPIO directions */
	
	/*
	 * Set up SPI for AVR8
	 * Note: AVR's SS pin must be set to output, regardless of whether we
	 * actually use it. This is a requirement of SPI mster mode.
	 */
	sbi(DDR(AVR_SS_PORT),AVR_SS_PIN);
	
	/* Set SCK and MOSI as output */
	sbi(DDR(CONTROLLER_SCK_PORT),CONTROLLER_SCK_PIN);
	sbi(DDR(CONTROLLER_MOSI_PORT),CONTROLLER_MOSI_PIN);
	
	/*
	 * Set MISO as input with pullup. This needs to be set for
	 * SPI to work, even though we never use or read it.
	 */
	cbi(DDR(CONTROLLER_MISO_PORT),CONTROLLER_MISO_PIN); // B3 MISO as input
	sbi(CONTROLLER_MISO_PORT,CONTROLLER_MISO_PIN);
	
	/* Set pin to controller SS as output */
	sbi(DDR(CONTROLLER_SS_PORT),CONTROLLER_SS_PIN); // A5

	/* Set LCD A0 pin as output */
	sbi(DDR(CONTROLLER_A0_PORT),CONTROLLER_A0_PIN); // A6
		
	/* Init SS pin high (i.e LCD deselected) */
	sbi(CONTROLLER_SS_PORT,CONTROLLER_SS_PIN);

	/* Deselect LCD */
	GLCD_DESELECT();

	/* MSB first, double speed, SPI mode 0 */
	SPCR = (1<<SPE) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA);	
	sbi(SPSR,SPI2X);
	
	/* Enable interrupts */
	sei();
		
	delay_ms(30); /* Example in datasheet does this (20ms) */

	glcd_ST7565R_init();

	glcd_all_on();
	
	delay_ms(500);
	glcd_normal();

	glcd_set_start_line(0);
	glcd_clear_now();
			
	glcd_select_screen(glcd_buffer,&glcd_bbox);
	
	glcd_clear();	
	
#else
	#error "Controller not supported"
#endif /* GLCD_CONTROLLER_* */
	
}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SPDR = c;
	while(!(SPSR & (1<<SPIF))); /* wait until transmission is complete */
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

#endif /* defined(GLCD_DEVICE_AVR8) */
