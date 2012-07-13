#include "../glcd.h"
#include "LPC11Uxx.h"


#if defined(GLCD_DEVICE_LPC11UXX)

void glcd_init(void)
{

#if defined(GLCD_CONTROLLER_PCD8544)
	/*
	 * Set up SPI (SSP)
	 * Note: Max allowed SPI clock is 4 MHz from datasheet.
	 */

	/* Select SSP/SPI port */
	SSP_IOConfig( CONTROLLER_SPI_PORT_NUMBER );

	/* Initialise SSP/SPI port */
	SSP_Init( CONTROLLER_SPI_PORT_NUMBER );

	/* Above functions take care of SPI pins */

	/* Set SS, DC and RST pins to output */
	CONTROLLER_SS_PORT->DIR  |= (1 << CONTROLLER_SS_PIN);
	CONTROLLER_DC_PORT->DIR  |= (1 << CONTROLLER_DC_PIN);
	CONTROLLER_RST_PORT->DIR |= (1 << CONTROLLER_RST_PIN);

	/* Deselect LCD */
	GLCD_DESELECT();

	/* Reset the display */
	glcd_reset();

	/* Get into the EXTENDED mode! */
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);

	/* LCD bias select (4 is optimal?) */
	glcd_command(PCD8544_SET_BIAS | 0x2);

	/* Set VOP */
	glcd_command(PCD8544_SET_VOP | 50); // Experimentally determined

	/* Back to standard instructions */
	glcd_command(PCD8544_FUNCTION_SET);

	/* Normal mode */
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);

	glcd_select_screen((uint8_t *)&glcd_buffer,&glcd_bbox);

	glcd_clear();

#elif defined(GLCD_CONTROLLER_NT75451)
	/* Parallel interface controller used on NGX BlueBoards */
	
	
#else /* GLCD_CONTROLLER_PCD8544 */
	#error "Controller not supported by LPC111x"
#endif

}

#if defined(GLCD_USE_PARALLEL)

void glcd_parallel_write(uint8_t c)
{

	
}

#else

void glcd_spi_write(uint8_t c)
{
	GLCD_SELECT();
	SSP_Send(CONTROLLER_SPI_PORT_NUMBER,&c,1);
	GLCD_DESELECT();
}

#endif /* GLCD_USE_PARALLEL */

void glcd_reset(void)
{
#if defined(GLCD_CONTROLLER_PCD8544)
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	_delay_ms(1);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
	
#elif defined(GLCD_CONTROLLER_NT75451)
	
#endif /* GLCD_CONTROLLER_PCD8544 */	
}

#endif /* GLCD_DEVICE_LPC11UXX */
