/*
 * AVR8.c
 *
 * Created: 25/03/2012 11:47:26 PM
 *  Author: andy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"
#include "../PCD8544.h"

extern uint8_t *pcd8544_buffer;
extern PCD8544_BoundingBox_t pcd8544_bbox;
extern uint8_t *pcd8544_buffer_selected;
extern PCD8544_BoundingBox_t *pcd8544_bbox_selected;

#if defined(PCD8544_DEVICE_AVR8)

void PCD8544_init(void)
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
	PCD8544_DESELECT();

	// Max allowed SPI clock is 4 MHz from datasheet.
	// Enable SPI, set master mode and clock rate to /4 (4MHz with F_CPU=8MHz)
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR = 0;
	
	PCD8544_reset();
	
	// get into the EXTENDED mode!
	PCD8544_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION );

	// LCD bias select (4 is optimal?)
	PCD8544_command(PCD8544_SET_BIAS | 0x2);
	
	// set VOP
	PCD8544_command(PCD8544_SET_VOP | 50); // Experimentally determined
	
	// back to standard instructions
	PCD8544_command(PCD8544_FUNCTION_SET); 
	
	// normal mode
	PCD8544_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);

	PCD8544_select_screen((uint8_t *)&pcd8544_buffer,&pcd8544_bbox);
	
	PCD8544_clear();
}

void PCD8544_spi_write(uint8_t c)
{
	PCD8544_SELECT();
	SPDR = c;
	while(!(SPSR & (1<<SPIF))); // wait until transmission is complete
	PCD8544_DESELECT();	
}

void PCD8544_reset(void)
{
	// toggle RST low to reset. Minimum pulse 100ns on datasheet.
	PCD8544_SELECT();
	PCD8544_RESET_LOW();
	_delay_ms(100);
	PCD8544_RESET_HIGH();
	PCD8544_DESELECT();	
}

#endif