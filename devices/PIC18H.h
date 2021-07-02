/**
   \file PIC18H.h
   \brief Functions relating to Microchip PIC18H (8-bit).
          For use with xc8 compiler.
   \author Andy Gock (adapted by David Gautier for PIC18)
 */
/*
	Copyright (c) 2013, Andy Gock

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

#ifndef GLCD_PINOUTS_PIC18H_H_
#define GLCD_PINOUTS_PIC18H_H_

#if defined(GLCD_DEVICE_USER)
	#include "glcd_user_config.h"
	#include "glcd_user_config.c"
#else

#if defined(GLCD_DEVICE_PIC18H)

#include <stdint.h>
#include <xc.h>


#if defined(GLCD_CONTROLLER_ST7565R)

/**
 * \name Other pins needed for serial LCD controller
 * @{
 */
#define CONTROLLER_SS_TRIS   TRISB0
#define CONTROLLER_SS_PIN    LATB0
#define CONTROLLER_A0_TRIS   TRISA2
#define CONTROLLER_A0_PIN    LATA2
#define CONTROLLER_RST_TRIS  TRISC1
#define CONTROLLER_RST_PIN   LATC1
	/**@}*/
#elif defined(GLCD_CONTROLLER_SSD1309)

#if defined(GLCD_CONTROLLER_SSD1309_SPI)
#define CONTROLLER_RST_TRIS  TRISC2
#define CONTROLLER_RST_PIN   LATC2
#define CONTROLLER_SS_TRIS   TRISC7
#define CONTROLLER_SS_PIN    LATC7
#define CONTROLLER_A0_TRIS   TRISC6
#define CONTROLLER_A0_PIN    LATC6

#else //I2C
#define CONTROLLER_RST_TRIS  TRISC1
#define CONTROLLER_RST_PIN   LATC1
#endif

#else
#error "Controller not supported or defined in PIC18H module"
#endif



/**
 * \name Macros for control lines
 * @{
 */
#define GLCD_SELECT()     CONTROLLER_SS_PIN = 0
#define GLCD_DESELECT()   CONTROLLER_SS_PIN = 1
#define GLCD_DC_LOW()     CONTROLLER_DC_PIN = 0
#define GLCD_DC_HIGH()    CONTROLLER_DC_PIN = 1
#define GLCD_RESET_LOW()  CONTROLLER_RST_PIN = 0
#define GLCD_RESET_HIGH() CONTROLLER_RST_PIN = 1
#define GLCD_A0_LOW()     CONTROLLER_A0_PIN = 0 /* Command write */
#define GLCD_A0_HIGH()    CONTROLLER_A0_PIN = 1 /* Write to display RAM */

/**@}*/

#endif /* GLCD_DEVICE_PIC18H */

#endif /* GLCD_DEVICE_USER */

#endif /* GLCD_PINOUTS_PIC18_H_ */
