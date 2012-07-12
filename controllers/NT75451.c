#if defined(GLCD_CONTROLLER_NT75451)

#include "../glcd.h"

void glcd_command(uint8_t c)
{

}

void glcd_data(uint8_t c)
{
}

void glcd_set_contrast(uint8_t val) {
}

void glcd_power_down(void)
{
}

void glcd_power_up(void)
{
}

void glcd_set_y_address(uint8_t y)
{
}

void glcd_set_x_address(uint8_t x)
{
}

void glcd_write()
{
	uint8_t bank;
	
#define PCD8544_MAX_BANKS 10 /* dummy val */
	for (bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
		/* Each bank is a single row 8 bits tall */
		uint8_t column;		
		
		if (glcd_bbox_selected->y_min >= (bank+1)*8) {
			continue; /* Skip the entire bank */
		}
		
		if (glcd_bbox_selected->y_max < bank*8) {
			break;    /* No more banks need updating */
		}
		
		//glcd_command(PCD8544_SET_Y_ADDRESS | bank);
		//glcd_command(PCD8544_SET_X_ADDRESS | glcd_bbox_selected->x_min);

		for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
		{
			//glcd_data( glcd_buffer_selected[PCD8544_MAX_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();
	
}

#endif
