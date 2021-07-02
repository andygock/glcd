/**
 * \file SSD1309_H_.c
 * \brief Functions relating to SSD1309 works with SPI or I2C.
 * \author David Gautier (modified from ST7565R.c by Andy Gock)
 * \see glcd.h
 */

#if defined(GLCD_CONTROLLER_SSD1309)

#include "../glcd.h"
#include <string.h>

uint8_t buf[4];
uint8_t buftest[10];
uint8_t bufpage[GLCD_LCD_WIDTH+1];


void glcd_command(uint8_t c)
{
	#if defined(GLCD_CONTROLLER_SSD1309_SPI)
    GLCD_A0_LOW();
		glcd_spi_write(c);

    #else
    buf[0]=COMMAND_BYTE;
    buf[1] = c;
    i2c_writeNBytes(SLAVE_ADDR,buf,2);
    #endif

}

void glcd_data(uint8_t c)
{
	#if defined(GLCD_CONTROLLER_SSD1309_SPI)
    GLCD_A0_HIGH();
		glcd_spi_write(c);
    #else // I2C
    buf[0]= DATA_BYTE;
    buf[1] = c;
    i2c_writeNBytes(SLAVE_ADDR,buf,2);
    i2c_writeNBytes(SLAVE_ADDR,0x00,1);
    #endif
}

#if ! defined(GLCD_CONTROLLER_SSD1309_SPI)
void glcd_test_data()
{
    glcd_command(SSD1309_SET_ADDRESS_MODE);
    glcd_set_y_address(0);
    glcd_set_x_address(0);
    buftest[0]=DATA_BYTE;
    buftest[1] = 0xFF;
    buftest[2] = 0xFF;
    buftest[3] = 0x00;
    buftest[4] = 0x01;
    buftest[5] = 0x02;
    buftest[6] = 0x04;
    buftest[7] = 0x08;
    buftest[8] = 0x10;
    buftest[9] = 0x20;
    i2c_writeNBytes(SLAVE_ADDR,buftest,10);
}

void glcd_datastream(uint8_t * buf, size_t length)
{
    bufpage[0]= DATA_BYTE;
    memcpy(bufpage+1,buf,length);
    i2c_writeNBytes(SLAVE_ADDR,bufpage,length+1);
}
#endif

void glcd_set_contrast(uint8_t val) {

    #if defined(GLCD_CONTROLLER_SSD1309_SPI)
    /* Can set a 6-bit value (0 to 63)  */

    /* Must send this command byte before setting the contrast */
    glcd_command(0x81);
    glcd_command(val);
    return;
    #else/* Can set a 6-bit value (0 to 63)  */
    buf[0] = COMMAND_BYTE;
    buf[1] = 0x81;
    buf[2] = COMMAND_BYTE;
    buf[3] = val;
    i2c_writeNBytes(SLAVE_ADDR,buf,4);
    #endif
}

void glcd_power_down(void)
{
	// Command sequence as in SSD1309 datasheet
	glcd_command(0xac);	// Static indicator off
	glcd_command(0x00);	// Static indicator register, not blinking
	glcd_command(0xae); // Display OFF
	glcd_command(0xa5); // Display all points ON

	// Display is now in sleep mode
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
	glcd_command(SSD1309_PAGE_ADDRESS_SET | (0x0F & y)); /* 0x0F = 0b00001111 */
}

void glcd_set_x_address(uint8_t x)
{
	glcd_set_column_upper(x);
	glcd_set_column_lower(x);
}

void glcd_all_on(void)
{
	glcd_command(SSD1309_DISPLAY_ALL_ON);
}

void glcd_normal(void)
{
	glcd_command(SSD1309_DISPLAY_NORMAL);
}

void glcd_set_column_upper(uint8_t addr)
{
	glcd_command(SSD1309_COLUMN_ADDRESS_SET_UPPER | (addr >> 4));
}

void glcd_set_column_lower(uint8_t addr)
{
	glcd_command(SSD1309_COLUMN_ADDRESS_SET_LOWER | (0x0f & addr));
}

void glcd_set_start_line(uint8_t addr)
{
	glcd_command( SSD1309_SET_START_LINE | (0x3F & addr)); /* 0x3F == 0b00111111 */
}
void glcd_set_page_mode()
{
	glcd_command( 0x20 );
    glcd_command( 0x02 );

}
/** Clear the display immediately, does not buffer */
void glcd_clear_now(void)
{
    uint8_t page;

	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
        uint8_t col;
        glcd_set_page_mode()	;
        glcd_set_y_address(page);
				glcd_set_x_address(0);
    		#if defined(GLCD_CONTROLLER_SSD1309_SPI)
				for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
					glcd_data(0);
				}
        #else
				glcd_datastream(zero,GLCD_LCD_WIDTH);
        #endif

	}
}


void glcd_pattern(void)
{
	uint8_t page;
	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
		uint8_t col;
    glcd_set_page_mode();
		glcd_set_y_address(page);
		glcd_set_x_address(0);
		for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
			glcd_data( (col / 8 + 2) % 2 == 1 ? 0xff : 0x00 );
		}
	}
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
	glcd_set_page_mode();
	glcd_set_y_address(bank);
	glcd_set_x_address(glcd_bbox_selected->x_min);
	#if defined(GLCD_CONTROLLER_SSD1309_SPI)
	for (column = glcd_bbox_selected->x_min; column <= glcd_bbox_selected->x_max; column++)
	{
			glcd_data( glcd_buffer_selected[GLCD_NUMBER_OF_COLS * bank + column] );
	}
  #else // I2C
  glcd_datastream(&(*glcd_buffer_selected) + (GLCD_NUMBER_OF_COLS * bank + glcd_bbox_selected->x_min) , glcd_bbox_selected->x_max-glcd_bbox_selected->x_min +1);
  #endif
	}
	glcd_reset_bbox();

}

void glcd_SSD1309_init(void) {


	/* Default init sequence */
	glcd_command(SSD1309_NORMAL);  //0xA6 // normal display
	glcd_command(SSD1309_DISPLAY_ON);
	glcd_set_contrast(255);

}
#endif /* defined(GLCD_CONTROLLER_SSD1309) */
