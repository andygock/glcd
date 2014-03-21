#include "../glcd.h"

#if defined(GLCD_DEVICE_USER)
	#include "glcd_user_config.h"
	#include "glcd_user_config.c"
#else

#if defined(GLCD_DEVICE_PIC32)

void glcd_init(void)
{
#if defined(GLCD_CONTROLLER_PCD8544)

	/* Set up remappable outputs for PIC32, SPI: DO and SCK */
   SpiChnOpen(SPI_CHANNEL2, SPI_CON_ON|SPI_CON_MSTEN, 4);

	/* Set SS, DC and RST pins as output */
	PORTSetPinsDigitalOut(LCD_CS_PORT, LCD_CS_PIN);
	PORTSetPinsDigitalOut(LCD_DC_RESET_PORT, LCD_DC_PIN | LCD_RESET_PIN);

	/* Deselect LCD */
	GLCD_DESELECT();

	/* Send reset pulse to LCD */
	glcd_reset();

	/* Initialise the display */
	glcd_PCD8544_init();

	/* Select screen buffer */
	glcd_select_screen(glcd_buffer,&glcd_bbox);

	/* Clear screen, we are now ready to go */
	glcd_clear();
#else
#error "Controller not supported"
#endif /* GLCD_CONTROLLER_* */
}

void glcd_spi_write(uint8_t c)
{
   GLCD_SELECT();
   SpiChnPutC(SPI_CHANNEL2, c);
   // Wait until the byte is sent before deselecting
   while(SpiChnIsBusy(SPI_CHANNEL2));
   GLCD_DESELECT();
}

void glcd_reset(void)
{
	GLCD_SELECT();
	GLCD_RESET_LOW();
	delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
   // Wait until the byte is sent before deselecting
   while(SpiChnIsBusy(SPI_CHANNEL2));
   GLCD_DESELECT();
}

#endif /* defined(GLCD_DEVICE_PIC32) */

#endif /* GLCD_DEVICE_USER */
