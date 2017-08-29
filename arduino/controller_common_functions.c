/*

Arduino implementation of controller interface routines.

This was written to permit dynamic selection of LCD types. Normally this would be
made by macro definitions by passing "-D" switches to the compiler.

If you make changes to the commands here, make sure you make the same corresponding
changes to "glcd/controllers/XXX.c" so that non arduino users will be able to
use your changes too.

*/

#include "../glcd.h"
#include "../controllers/PCD8544.h"
#include "../controllers/ST7565R.h"
#include "../controllers/NT75451.h" /* not implemented */
#include "avr8.h"

#if defined(USE_ARDUINO)

void glcd_command(uint8_t c)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		GLCD_DC_LOW();
		glcd_spi_write(c);
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		GLCD_A0_LOW();
		glcd_spi_write(c);
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_data(uint8_t c)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		GLCD_DC_HIGH();
		glcd_spi_write(c);
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		GLCD_A0_HIGH();
		glcd_spi_write(c);
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_set_contrast(uint8_t val) {
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);
		glcd_command(PCD8544_SET_VOP | (val&0x7f));
		glcd_command(PCD8544_FUNCTION_SET);
		glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		/* Can set a 6-bit value (0 to 63)  */

		/* Must send this command byte before setting the contrast */
		glcd_command(0x81);

		/* Set the contrat value ("electronic volumne register") */
		if (val > 63) {
			glcd_command(63);
		} else {
			glcd_command(val);
		}
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_power_down(void)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		/* First, fill RAM with zeroes to ensure minimum specified current consumption */
		glcd_clear();

		/* Power down */
		glcd_command(PCD8544_FUNCTION_SET|PCD8544_POWER_DOWN);
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		/* Command sequence as in ST7565 datasheet */
		glcd_command(0xac);	// Static indicator off
		glcd_command(0x00);	// Static indicator register, not blinking
		glcd_command(0xae); // Display OFF
		glcd_command(0xa5); // Display all points ON

		/* Display is now in sleep mode */
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_power_up(void)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		glcd_command(PCD8544_FUNCTION_SET);
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		glcd_command(0xa4); // Display all points OFF
		glcd_command(0xad);	// Static indicator ON
		glcd_command(0x00);	// Static indicator register, not Blinking
		glcd_command(0xaf);
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_set_y_address(uint8_t y)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		glcd_command(PCD8544_SET_Y_ADDRESS|(y > 5 ? 5 : y));
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		glcd_command(ST7565R_PAGE_ADDRESS_SET | (0x0F & y)); /* 0x0F = 0b00001111 */
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_set_x_address(uint8_t x)
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		glcd_command(PCD8544_SET_X_ADDRESS|(x & 0x7f));
	} else if (glcd_pinmap.controller == GLCD_TYPE_ST7565R) {
		glcd_set_column_upper(x);
		glcd_set_column_lower(x);
	} else {
		/* Unsupported GLCD controller */
	}
}

void glcd_write()
{
	if (glcd_pinmap.controller == GLCD_TYPE_PCD8544) {
		uint8_t bank;

		for (bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
			/* Each bank is a single row 8 bits tall */
			uint8_t column;

			if (glcd_bbox_selected->y_min >= (bank+1)*8) {
				continue; /* Skip the entire bank */
			}

			if (glcd_bbox_selected->y_max < bank*8) {
				break;    /* No more banks need updating */
			}

			glcd_command(PCD8544_SET_Y_ADDRESS | bank);
			glcd_command(PCD8544_SET_X_ADDRESS | glcd_bbox_selected->x_min);

			for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
			{
				glcd_data( glcd_buffer_selected[PCD8544_MAX_COLS * bank + column] );
			}
		}

		glcd_reset_bbox();
	} else {
		/* Unsupported GLCD controller */
	}

}

#endif
