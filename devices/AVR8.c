/**
   \file AVR8.c
   \brief Functions relating to Atmel AVR 8-bit AVRs.
   \author Andy Gock

 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"
#include "../glcd.h"

extern uint8_t *glcd_buffer;
extern glcd_BoundingBox_t glcd_bbox;
extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;

#if defined(GLCD_DEVICE_AVR8)

void glcd_init(void)
{
	// set pin directions
	
	// Set MOSI, Master SS, SCK to output (otherwise SPI won't work)
	// must be done even if native SS pin not used
	sbi(DDR(PCD8544_MOSI_PORT),PCD8544_MOSI_PIN);
	sbi(DDR(PCD8544_SS_PORT),PCD8544_SS_PIN);
	sbi(DDR(PCD8544_SCK_PORT),PCD8544_SCK_PIN);
		
	// set SS, DC and RST pins to output
	sbi( DDR(PCD8544_SS_PORT), PCD8544_SS_PIN );
	sbi( DDR(PCD8544_DC_PORT), PCD8544_DC_PIN );
	sbi( DDR(PCD8544_RST_PORT), PCD8544_RST_PIN );
	
	// deselect LCD
	GLCD_DESELECT();

	// Max allowed SPI clock is 4 MHz from datasheet.
	// Enable SPI, set master mode and clock rate to /4 (4MHz with F_CPU=8MHz)
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR = 0;
	
	glcd_reset();
	
	// get into the EXTENDED mode!
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION );

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
}

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SPDR = c;
	while(!(SPSR & (1<<SPIF))); // wait until transmission is complete
	GLCD_DESELECT();	
}

void glcd_reset(void)
{
	// toggle RST low to reset. Minimum pulse 100ns on datasheet.
	GLCD_SELECT();
	GLCD_RESET_LOW();
	_delay_ms(100);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();	
}

#endif