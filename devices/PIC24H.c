/**
   \file PIC24H.c
   \brief Functions relating to Microchip PIC24H (16-bit).
          For use with xc16 compiler.
   \author Andy Gock
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

#include "PIC24H.h"

#if defined(GLCD_DEVICE_PIC24H)

void glcd_init(void)
{
	
#if defined(GLCD_CONTROLLER_PCD8544)
	
	/* Set up remappable outputs for PIC24H, SPI: DO and SCK */
	OSCCONbits.IOLOCK = 0;
	REGISTER_MAP_SPI_DO = 0b00111; /* Set as SPI DO */
	REGISTER_MAP_SPI_SCK = 0b01000; /* Set as SCK */
	OSCCONbits.IOLOCK = 1;

	/* Set DO and SCK pins as output */
	CONTROLLER_MISO_TRIS = 0;
	CONTROLLER_SCK_TRIS = 0;

	/* If the pins is also an ADC port, set these as digital mode */
	// Do we really need to do this, or will setting RPxR deal with this
	//_PCFG9 = 1;
	//_PCFG10 = 1;

	/* Set SS, DC and RST pins as output */
	CONTROLLER_SS_TRIS = 0;
	CONTROLLER_DC_TRIS = 0;
	CONTROLLER_RST_TRIS = 0;

	/* Deselect LCD */
	GLCD_DESELECT();

	/* SPI setup based on sample code from datasheet */
	/* The following code shows the SPI register configuration for Master mode */
	IFS0bits.SPI1IF = 0; /* Clear the Interrupt Flag */
	IEC0bits.SPI1IE = 0; /* Disable the Interrupt */

	/* SPI1CON1 Register Settings */
	SPI1CON1bits.DISSCK = 0; /* Internal Serial Clock is Enabled */
	SPI1CON1bits.DISSDO = 0; /* SDOx pin is controlled by the module */
	SPI1CON1bits.MODE16 = 0; /* Communication is word-wide (16 bits) */
	SPI1CON1bits.SMP = 0;    /* Input data is sampled at the middle of data */
	SPI1CON1bits.CKE = 0;    /* Serial output data changes on transition */
	SPI1CON1bits.CKP = 0;    /* Idle state for clock is a low level */
	SPI1CON1bits.PPRE = 0b11;  /* Primary prescale = 1:1 */
	SPI1CON1bits.SPRE = 0b001; /* Secondary prescale = 4:1 */
	SPI1CON1bits.MSTEN = 1;  /* Master mode Enabled */
	SPI1STATbits.SPIEN = 1;  /* Enable SPI module */

	/* Interrupt Controller Settings */
	// we're not using interrupts to handle SPI
	//IFS0bits.SPI1IF = 0; /* Clear the Interrupt Flag */
	//IEC0bits.SPI1IE = 1; /* Enable the Interrupt */

	/* Send reset pulse to LCD */
	glcd_reset();
	
	/* Get into the EXTENDED mode! */
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);

	/* LCD bias select (4 is optimal?) */
	glcd_command(PCD8544_SET_BIAS | 0x2);
	
	/* Set VOP (affects contrast) */
	glcd_command(PCD8544_SET_VOP | 80); /* Experimentally determined, play with this figure until contrast looks nice */
	
	/* Back to standard instructions */
	glcd_command(PCD8544_FUNCTION_SET); 
	
	/* Normal mode */
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);

	/* Select screen buffer */
	glcd_select_screen(glcd_buffer,&glcd_bbox);
	
	/* Clear screen, we are now ready to go */
	glcd_clear();

#elif defined(GLCD_CONTROLLER_ST7565R)
	//#error "ST7565R not supported on PIC24H yet"

	/* Set up remappable outputs for PIC24H, SPI: DO and SCK */
	OSCCONbits.IOLOCK = 0;
	REGISTER_MAP_SPI_DO = 0b00111; /* Set as SPI DO */
	REGISTER_MAP_SPI_SCK = 0b01000; /* Set as SCK */
	OSCCONbits.IOLOCK = 1;

	/* Set DO and SCK pins as output */
	CONTROLLER_MOSI_TRIS = 0;
	CONTROLLER_SCK_TRIS = 0;

	/* Set SS, DC and A0 pins as output */
	CONTROLLER_SS_TRIS = 0;
	CONTROLLER_A0_TRIS = 0;
	CONTROLLER_RST_TRIS = 0;
	
	/* Deselect LCD */
	GLCD_DESELECT();

	/* SPI setup based on sample code from datasheet */
	/* The following code shows the SPI register configuration for Master mode */
	IFS0bits.SPI1IF = 0; /* Clear the Interrupt Flag */
	IEC0bits.SPI1IE = 0; /* Disable the Interrupt */

	/* SPI1CON1 Register Settings */
	SPI1CON1bits.DISSCK = 0; /* Internal Serial Clock is Enabled */
	SPI1CON1bits.DISSDO = 0; /* SDOx pin is controlled by the module */
	SPI1CON1bits.MODE16 = 0; /* Communication is word-wide (16 bits) */
	SPI1CON1bits.SMP = 0;    /* Input data is sampled at the middle of data */
	SPI1CON1bits.CKE = 0;    /* Serial output data changes on transition */
	SPI1CON1bits.CKP = 0;    /* Idle state for clock is a low level */
	SPI1CON1bits.PPRE = 0b11;  /* Primary prescale = 1:1 */
	SPI1CON1bits.SPRE = 0b001; /* Secondary prescale = 4:1 */
	SPI1CON1bits.MSTEN = 1;  /* Master mode Enabled */
	SPI1STATbits.SPIEN = 1;  /* Enable SPI module */

	/* Set up GPIO directions */
	//delay_ms(30); // example in datasheet does this (20ms)

	//glcd_command(ST7565R_RESET); // internal reset

	/*
	glcd_command(0xa2); // 1/9 bias
	glcd_command(0xa0); // ADC select, normal
	glcd_command(0xc8); // com output reverse
	glcd_command(0xa4); // display all points normal
	glcd_command(0x40); // display start line set
	glcd_command(0x25); // internal resistor ratio
	glcd_command(0x81); // electronic volume mode set
	//glcd_command(0x10); // electronic volume - datasheet's contrast example doesn't work
	glcd_command(45); // this works better
	glcd_command(0x2f); // power controller set
	glcd_command(0xaf); // display on
	*/

	/* Send reset pulse to LCD */
	glcd_reset();
	delay_ms(100);

	/* Init sequence based on datasheet code for NHD-C12832A1Z-FSW-FBW-3V3 */
	/* Datasheet says max SCK frequency 20MHz, scope measurement shows around 3-4 MHz */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc0); /* Common output mode select: normal direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x21); /* Internal resistor radio, set to: 1 */

#if 0 /* Don't use datasheet's contrast default value, it is too high */
	glcd_command(0x81); /* Electronic volume mode set */
	glcd_command(0x3f); /* Electronic volume register set (contrast), datasheets value (63, which is max value) */
#endif

	/* End of sample code's init sequence, everything below us our own doing */
	
	/* Set contrast, value experimentally determined */
	glcd_set_contrast(40); /* Can set to 6-bit value, 0 to 63)*/
	
	glcd_command(0xaf); /* Display on */

	glcd_all_on();
	
	delay_ms(500);
	glcd_normal();

	glcd_set_start_line(0);
	glcd_clear_now();
			
	glcd_select_screen(glcd_buffer,&glcd_bbox);
	
	glcd_clear();	
	
#else
	#error "Controller not supported"
#endif /* GLCD_CONTROLLER_PCD8544 */
	
}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	
    while (SPI1STATbits.SPITBF); /* Loop until TX buffer is empty */
	SPI1BUF = (c & 0x00FF); /* Write data to be transmitted */
	while(!SPI1STATbits.SPIRBF); /* Wait until TX finished */

	uint8_t read;
	read = SPI1BUF; /* Throw away the data (not sure if this is neccesary, to force reading of SPI1BUF) */

	GLCD_DESELECT();
}

void glcd_reset(void)
{
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	__delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();	
}

#endif /* defined(GLCD_DEVICE_PIC24H) */

#endif /* GLCD_DEVICE_USER */