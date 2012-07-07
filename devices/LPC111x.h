/**
 * \file LPC111x.h
 * \brief Pinouts and driver config for NXP LPC111x ARM Cortex-M0 MCUs.
 * \author Andy Gock
 */

/*

	Copyright (c) 2012 Andy Gock

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#ifndef LPC111X_H_
#define LPC111X_H_

#if defined(GLCD_DEVICE_LPC111X)

/*
 * Set up SSP and GPIO drivers (GPIO drivers required for SSP)
 * Change these paths if the files are located elsewhere
 */
#include "../../drivers/ssp.h"
#include "../../drivers/gpio.h"

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

/* Define port and pins used to connecto LCD */
#define CONTROLLER_SPI_PORT_NUMBER 1
#define CONTROLLER_MOSI_PORT LPC_GPIO2
#define CONTROLLER_MOSI_PIN  3
#define CONTROLLER_MISO_PORT LPC_GPIO2
#define CONTROLLER_MISO_PIN  2
#define CONTROLLER_SCK_PORT  LPC_GPIO2
#define CONTROLLER_SCK_PIN   1
#define CONTROLLER_SS_PORT   LPC_GPIO2
#define CONTROLLER_SS_PIN    0
#define CONTROLLER_DC_PORT   LPC_GPIO2
#define CONTROLLER_DC_PIN    4
#define CONTROLLER_RST_PORT  LPC_GPIO2
#define CONTROLLER_RST_PIN   5

/* Preprocessor macros */
#define GLCD_SELECT()     CONTROLLER_SS_PORT->DATA  &= ~(1 << CONTROLLER_SS_PIN)
#define GLCD_DESELECT()   CONTROLLER_SS_PORT->DATA  |=  (1 << CONTROLLER_SS_PIN)
#define GLCD_DC_LOW()     CONTROLLER_DC_PORT->DATA  &= ~(1 << CONTROLLER_DC_PIN)
#define GLCD_DC_HIGH()    CONTROLLER_DC_PORT->DATA  |=  (1 << CONTROLLER_DC_PIN)
#define GLCD_RESET_LOW()  CONTROLLER_RST_PORT->DATA &= ~(1 << CONTROLLER_RST_PIN)
#define GLCD_RESET_HIGH() CONTROLLER_RST_PORT->DATA |=  (1 << CONTROLLER_RST_PIN)

#endif /* GLCD_DEVICE_LPC111X */

#endif /* LPC111X_H_ */
