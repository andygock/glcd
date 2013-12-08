/**
	\file RASPBERRYPI.c
	\author HanChen
	\brief Functions specific to RaspberryPi devices.
 */

/*
	Copyright (c) 2012, Andy Gock

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of Andy Gock nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL ANDY GOCK BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined(GLCD_DEVICE_RASPBERRYPI)

/* Includes from BCM2835 Library */
#include <bcm2835.h>
/* Includes from GLCD */
#include "../glcd.h"
#include "inc/RASPBERRYPI.h"

int glcd_init(void)
{
    if (!bcm2835_init()) return 1;

#if !defined(GLCD_USE_PARALLEL)
    if (!bcm2835_spi_begin()) return 2;
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default

#else
    #error 'Parallel not supported'
#endif

#if defined(GLCD_CONTROLLER_ST7565R)
    bcm2835_gpio_fsel(CONTROLLER_GPIO_RESET_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CONTROLLER_GPIO_RS_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CONTROLLER_GPIO_LEDA_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(CONTROLLER_GPIO_RESET_PIN, LOW);
    delay_ms(50);
    bcm2835_gpio_write(CONTROLLER_GPIO_RESET_PIN, HIGH);
    delay_ms(50);
    glcd_rs_cmd();
    glcd_spi_write(ST7563R_POWER_SET_1);
    glcd_spi_write(ST7563R_POWER_SET_2);
    glcd_spi_write(ST7563R_POWER_SET_3);
    glcd_spi_write(ST7563R_RESISTOR_RATIO_BASE & 0b00000011);
    glcd_spi_write(ST7563R_BIAS_SET_0);
    glcd_spi_write(ST7563R_SER_COM_D);
    glcd_spi_write(ST7565R_NORMAL);
    glcd_spi_write(ST7565R_DISPLAY_ON);
#else
	#error "Controller not supported by RASPBERRY"
#endif
    return 0;

}

void glcd_spi_write(uint8_t c)
{
    bcm2835_spi_chipSelect(CONTROLLER_SPI_CS);                      // The default
    bcm2835_spi_setChipSelectPolarity(CONTROLLER_SPI_CS, LOW);      // the default
    bcm2835_spi_transfer(c);
    bcm2835_spi_shipSelect(BCM2835_SPI_CS_NONE);
}

void glcd_reset(void)
{
    /* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
    bcm2835_gpio_write(CONTROLLER_GPIO_RESET_PIN, LOW);
    delay_ms(30);
    bcm2835_gpio_write(CONTROLLER_GPIO_RESET_PIN, HIGH);
}


void glcd_rs_data(void)
{
    bcm2835_gpio_write(CONTROLLER_GPIO_RS_PIN, HIGH);

}

void glcd_rs_cmd(void)
{
    bcm2835_gpio_write(CONTROLLER_GPIO_RS_PIN, LOW);
}

void glcd_close(void)
{
    bcm2835_spi_shipSelect(BCM2835_SPI_CS_NONE);
    bcm2835_spi_end();
    bcm2835_close();

}

#endif
