/**
 * \file ST7565R.c
 * \brief Functions relating to ST7565R.
 * \author Andy Gock
 * \see glcd.h
 */ 
#if defined(GLCD_CONTROLLER_ST7565R)

#include "../glcd.h"
#include "ST7565R.h"

void glcd_command(uint8_t c)
{
	GLCD_A0_LOW();
	glcd_spi_write(c);	
}

void glcd_data(uint8_t c)
{
	GLCD_A0_HIGH();
	glcd_spi_write(c);	
}

void glcd_set_contrast(uint8_t val) {
	/* Can set a 6-bit value (0 to 63)  */

	/* Must send this command byte before setting the contrast */
	glcd_command(0x81);
	
	/* Set the contrat value ("electronic volumne register") */
	if (val > 63) {
		glcd_command(63);
	} else {
		glcd_command(val);
	}
	return;
}

void glcd_power_down(void)
{
	/* Command sequence as in ST7565 datasheet */
	glcd_command(0xac);	// Static indicator off
	glcd_command(0x00);	// Static indicator register, not blinking
	glcd_command(0xae); // Display OFF
	glcd_command(0xa5); // Display all points ON

	/* Display is now in sleep mode */
}

void glcd_power_up(void)
{
	glcd_command(0xa4); // Display all points OFF
	glcd_command(0xad);	// Static indicator ON
	glcd_command(0x00);	// Static indicator register, not Blinking
	glcd_command(0xaf);

	return;
}

void glcd_set_y_address(uint8_t y)
{
	glcd_command(ST7565R_PAGE_ADDRESS_SET | (0x0F & y)); /* 0x0F = 0b00001111 */
}

void glcd_set_x_address(uint8_t x)
{
	glcd_set_column_upper(x);
	glcd_set_column_lower(x);	
}

void glcd_write()
{

	uint8_t bank;

	for (bank = 0; bank < GLCD_NUMBER_OF_BANKS; bank++) {
		/* Each bank is a single row 8 bits tall */
		uint8_t column;		
		
		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; /* Skip the entire bank */
		}
		
		if (glcd_bbox_selected->y_max < bank*8) {
			break;    /* No more banks need updating */
		}
		
		glcd_set_y_address(bank);
		glcd_set_x_address(glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			glcd_data( glcd_buffer_selected[GLCD_NUMBER_OF_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();

}

#endif /* defined(GLCD_CONTROLLER_ST7565R) */
