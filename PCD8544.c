/*
 * PCD8544.c
 *
 *
 */

#include <string.h>
#include <stdio.h>
#include "PCD8544.h"

// display buffer (504 bytes for 48x84 LCD)
uint8_t pcd8544_buffer[PCD8544_LCD_WIDTH * PCD8544_LCD_HEIGHT / 8];
PCD8544_BoundingBox_t pcd8544_bbox;

// pointers to buffer and bounding box for current screen being updated
uint8_t *pcd8544_buffer_selected;
PCD8544_BoundingBox_t *pcd8544_bbox_selected;

void PCD8544_command(uint8_t c)
{
	PCD8544_DC_LOW();
	PCD8544_spi_write(c);	
}

void PCD8544_data(uint8_t c)
{
	PCD8544_DC_HIGH();
	PCD8544_spi_write(c);	
}

void PCD8544_set_contrast(uint8_t val) {
	PCD8544_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);
	PCD8544_command(PCD8544_SET_VOP | (val|0x7f));
	PCD8544_command(PCD8544_FUNCTION_SET);
	PCD8544_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
}

void PCD8544_power_down(void)
{
	// first, fill RAM with zeroes to ensure minimum specified current consumption
	PCD8544_clear();
	
	// power down
	PCD8544_command(PCD8544_FUNCTION_SET|PCD8544_POWER_DOWN);
}

void PCD8544_power_up(void)
{
	PCD8544_command(PCD8544_FUNCTION_SET);
}

void PCD8544_set_y_address(uint8_t y)
{
	PCD8544_command(PCD8544_SET_Y_ADDRESS|(y > 5 ? 5 : y));
}

void PCD8544_set_x_address(uint8_t x)
{
	PCD8544_command(PCD8544_SET_X_ADDRESS|(x & 0x7f));
}

void PCD8544_write()
{
	uint8_t bank;
	
	for (bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
		uint8_t column;		
		
		if (pcd8544_bbox_selected->y_min >= (bank+1)*8) {
			continue; // skip the entire bank
		}
		
		if (pcd8544_bbox_selected->y_max < bank*8) {
			break;    // no more banks need updating
		}
		
		PCD8544_command(PCD8544_SET_Y_ADDRESS | bank);
		PCD8544_command(PCD8544_SET_X_ADDRESS | pcd8544_bbox_selected->x_min);

		for (column = pcd8544_bbox_selected->x_min; column <= pcd8544_bbox_selected->x_max; column++)
		{
			PCD8544_data( pcd8544_buffer_selected[PCD8544_MAX_COLS * bank + column] );
		}
	}

	PCD8544_reset_bbox();
	
}

void PCD8544_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
	if (xmin < pcd8544_bbox_selected->x_min) {
		pcd8544_bbox_selected->x_min = xmin;
	}		
	if (xmax > pcd8544_bbox_selected->x_max) {
		pcd8544_bbox_selected->x_max = xmax;
	}
	if (ymin < pcd8544_bbox_selected->y_min) {
		pcd8544_bbox_selected->y_min = ymin;
	}		
	if (ymax > pcd8544_bbox_selected->y_max) {
		pcd8544_bbox_selected->y_max = ymax;
	}			
}

void PCD8544_reset_bbox()
{
	pcd8544_bbox_selected->x_min = PCD8544_LCD_WIDTH - 1;
	pcd8544_bbox_selected->x_max = 0;
	pcd8544_bbox_selected->y_min = PCD8544_LCD_HEIGHT -1;
	pcd8544_bbox_selected->y_max = 0;	
}

void PCD8544_clear(void) {
	memset(pcd8544_buffer_selected, 0x00, PCD8544_LCD_WIDTH * PCD8544_LCD_HEIGHT / 8);
	PCD8544_update_bbox(0,0,PCD8544_LCD_WIDTH - 1,PCD8544_LCD_HEIGHT - 1);
	PCD8544_write();
}

void PCD8544_clear_buffer(void) {
	memset(pcd8544_buffer_selected, 0x00, PCD8544_LCD_WIDTH * PCD8544_LCD_HEIGHT / 8);
	PCD8544_update_bbox(0,0,PCD8544_LCD_WIDTH - 1,PCD8544_LCD_HEIGHT - 1);
}

void PCD8544_select_screen(uint8_t *buffer, PCD8544_BoundingBox_t *bbox)
{
	pcd8544_buffer_selected = buffer;
	pcd8544_bbox_selected = bbox;
}

void PCD8544_scroll(int8_t x, int8_t y)
{
	for (uint8_t y=0; y<6; y++) {
		for (uint8_t x=0; x<84; x++) {
			
		}
	}
}

void PCD8544_scroll_line(void)
{
	for (uint8_t y=0; y<6; y++) {
		if (y <= 4) {
			// first 5 lines - banks 0 to 4
			memcpy(pcd8544_buffer_selected + y*84, pcd8544_buffer_selected + y*84 + 84, 84);
		} else {
			// last line - back 5 - clear it
			memset(pcd8544_buffer_selected + 5*84, 0x00, 84);
		}
	}
	PCD8544_update_bbox(0,0,PCD8544_LCD_WIDTH - 1,PCD8544_LCD_HEIGHT - 1);
}