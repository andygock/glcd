/**
 * \file ST7565R.c
 * \brief Functions relating to ST7565R.
 * \author Andy Gock
 * \see glcd.h
 */ 
#if defined(GLCD_CONTROLLER_ST7565R)

#include "../glcd.h"

void glcd_command(uint8_t c)
{
	GLCD_DC_LOW();
	glcd_spi_write(c);	
}

void glcd_data(uint8_t c)
{
	GLCD_DC_HIGH();
	glcd_spi_write(c);	
}

void glcd_set_contrast(uint8_t val) {
	asm("break");
}

void glcd_power_down(void)
{
	asm("break");
}

void glcd_power_up(void)
{
	asm("break");
}

void glcd_set_y_address(uint8_t y)
{
	asm("break");
}

void glcd_set_x_address(uint8_t x)
{
	asm("break");
}

void glcd_all_on(void)
{
	glcd_command(0b10100101); // all display points on
}

void glcd_normal(void)
{
	glcd_command(0b10100100); // normal display
}

void glcd_set_page_address(uint8_t addr)
{
	glcd_command(0b10110000 | (0b00001111 & addr));
}

void glcd_set_column_upper(uint8_t addr)
{
	glcd_command(0b00010000 | (addr >> 4));
}

void glcd_set_column_lower(uint8_t addr)
{
	glcd_command(0x0f & addr);
}

void glcd_set_column(uint8_t addr)
{
	glcd_set_column_upper(addr);
	glcd_set_column_lower(addr);
}

void glcd_set_start_line(uint8_t addr)
{
	glcd_command(_BV(6) | (0b00111111 & addr));
}

/** Clear the display immediately, does not buffer */
void glcd_clear_now(void)
{
	for (uint8_t page = 0; page < 65; page++) {
		glcd_set_page_address(page);
		glcd_set_column(0);
		for (uint8_t col = 0; col < 133; col++) {
			glcd_data(0);
		}			
	}
}

void glcd_pattern(void)
{
	for (uint8_t page = 0; page < 65; page++) {
		glcd_set_page_address(page);
		glcd_set_column(0);
		for (uint8_t col = 0; col < 133; col++) {
			glcd_data( (col / 8 + 2) % 2 == 1 ? 0xff : 0x00 );
		}			
	}
}

void glcd_write()
{

	uint8_t bank;

	for (bank = 0; bank < GLCD_MAX_BANKS; bank++) {
		/* Each bank is a single row 8 bits tall */
		uint8_t column;		
		
		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; /* Skip the entire bank */
		}
		
		if (glcd_bbox_selected->y_max < bank*8) {
			break;    /* No more banks need updating */
		}
		
		glcd_set_page_address(bank);
		glcd_set_column(glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			glcd_data( glcd_buffer_selected[GLCD_MAX_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();

}

#endif