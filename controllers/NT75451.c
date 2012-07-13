#if defined(GLCD_CONTROLLER_NT75451)

#include "../glcd.h"

/* Remove this later */
void lcd_write_cmd(unsigned char command);

void glcd_command(uint8_t c)
{
	lcd_write_cmd((unsigned char)c);
	return;
	
	GLCD_RS_LOW();
	glcd_parallel_write(c);
	GLCD_RS_HIGH();	

	glcd_delay(50);	
}

void glcd_data(uint8_t c)
{
	GLCD_RS_HIGH();
	glcd_parallel_write(c);
	GLCD_RS_LOW();
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
	/** Code by NGX Technologies */
	glcd_command(0xB0 | (y > 8 ? 8 : y));
}

void glcd_set_x_address(uint8_t x)
{
	/** Code by NGX Technologies */
	uint8_t lsb, msb;
	
	msb	= (((x & 0xF0) >> 4)| 0x10);
	lsb	= (x & 0x0F);
	
	glcd_command(lsb);
	glcd_command(msb);	
}

/* Write screen buffer to display, within bounding box only */
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

	/* Display updated, we can reset the bounding box */
	glcd_reset_bbox();
	
}

#endif

/**
 * \todo All items need to be removed. It is from Keil / NGX sample code
 */

#define LCD_DATA_DIR	   LPC_GPIO->DIR[1]
#define LCD_DATA_SET	   LPC_GPIO->PIN[1]
#define LCD_DATA_CLR	   LPC_GPIO->PIN[1]
#define LCD_DATA_PIN	   LPC_GPIO->PIN[1]

#define LCD_CTRL_DIR	   LPC_GPIO->DIR[0]
#define LCD_CTRL_SET       LPC_GPIO->PIN[0]
#define LCD_CTRL_CLR       LPC_GPIO->PIN[0]
#define LCD_CTRL_PIN	   LPC_GPIO->PIN[0]
 
#define LCD_CTRL_CS_DIR		LPC_GPIO->DIR[1]
#define LCD_CTRL_CS_SET    	LPC_GPIO->PIN[1]
#define LCD_CTRL_CS_CLR    	LPC_GPIO->PIN[1]

#define LCD_CTRL_RST_DIR	LPC_GPIO->DIR[0]
#define LCD_CTRL_RST_SET    LPC_GPIO->PIN[0]
#define LCD_CTRL_RST_CLR    LPC_GPIO->PIN[0]

#define LCD_CTRL_BL_DIR		LPC_GPIO->DIR[1]
#define LCD_CTRL_BL_SET    	LPC_GPIO->PIN[1]
#define LCD_CTRL_BL_CLR    	LPC_GPIO->PIN[1]

#define LCD_D0 		1 << 19
#define LCD_D1 		1 << 20
#define LCD_D2 		1 << 21
#define LCD_D3 		1 << 22
#define LCD_D4 		1 << 26
#define LCD_D5 		1 << 27
#define LCD_D6 		1 << 28
#define LCD_D7 		1U <<31
  
#define LCD_BUSY_FLAG   LCD_D7									/* Enables LCD_BUSY_FLAG */

#define LCDRST 		(1 << 0)
#define LCDCS1B 	(1 << 13)
#define LCDRS	 	(1 << 14)
#define LCDRW	 	(1 << 13)
#define LCDEN 		(1 << 12)
#define LCDBL		(1 << 14)

#define GLCD_DATA_MASK_LOWER_NIBBLE  (LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3 )
#define GLCD_DATA_MASK_HIGHER_NIBBLE  (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7 )
#define GLCD_DATA_MASK (GLCD_DATA_MASK_LOWER_NIBBLE | GLCD_DATA_MASK_HIGHER_NIBBLE)

#define LCD_CTRL_MASK   (LCDRW | LCDRS)
#define LCD_CS  LCDCS1B
#define LCD_RST  LCDRST
#define LCD_BL   LCDBL
#define		HIGH	1
#define		LOW		0

void lcd_write_cmd(unsigned char command)
{
   
  unsigned int temp1=0, temp2=0, temp3=0;

	temp1 = command & 0x0F;
	temp1=temp1<<19;
	temp2 = command & 0x70;
	temp2 = temp2 <<22;
	temp3= command&0x80;
	temp3= temp3<<24;


	LCD_CTRL_CLR &= ~(LCDRS);
	LCD_CTRL_CS_CLR &= ~(LCDCS1B);
	LCD_CTRL_CLR &= ~(LCDRW);
	LCD_DATA_CLR &= ~(GLCD_DATA_MASK);
	LCD_DATA_SET |= temp1 | temp2 |temp3;
	glcd_delay(10);
	LCD_CTRL_SET |= LCDRW;
	LCD_CTRL_CS_SET |= LCDCS1B;
	LCD_CTRL_SET |= LCDRS;

}
