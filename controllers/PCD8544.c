/** Functions relating to PCD8544 LCD Controller (Nokia 5110 LCD).
   \author Andy Gock
 */ 

#if defined(GLCD_CONTROLLER_PCD8544)

#include "../glcd.h"

extern uint8_t *glcd_buffer_selected;
extern glcd_BoundingBox_t *glcd_bbox_selected;

void glcd_set_contrast(uint8_t val) {
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);
	glcd_command(PCD8544_SET_VOP | (val|0x7f));
	glcd_command(PCD8544_FUNCTION_SET);
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
}

void glcd_power_down(void)
{
	// first, fill RAM with zeroes to ensure minimum specified current consumption
	glcd_clear();
	
	// power down
	glcd_command(PCD8544_FUNCTION_SET|PCD8544_POWER_DOWN);
}

void glcd_power_up(void)
{
	glcd_command(PCD8544_FUNCTION_SET);
}

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

void glcd_set_y_address(uint8_t y)
{
	glcd_command(PCD8544_SET_Y_ADDRESS|(y > 5 ? 5 : y));
}

void glcd_set_x_address(uint8_t x)
{
	glcd_command(PCD8544_SET_X_ADDRESS|(x & 0x7f));
}

void glcd_write()
{
	uint8_t bank;
	
	for (bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
		uint8_t column;		
		
		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; // skip the entire bank
		}
		
		if (glcd_bbox_selected->y_max < bank*8) {
			break;    // no more banks need updating
		}
		
		glcd_command(PCD8544_SET_Y_ADDRESS | bank);
		glcd_command(PCD8544_SET_X_ADDRESS | glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			glcd_data( glcd_buffer_selected[PCD8544_MAX_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();
	
}

#endif