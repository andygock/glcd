/**
   \file PIC24H.c
   \brief Functions relating to Microchip PIC24H (16-bit).
          For use with xc16 compiler.
   \author Andy Gock
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

#ifndef GLCD_PINOUTS_PIC24H_H_
#define GLCD_PINOUTS_PIC24H_H_

#if defined(GLCD_DEVICE_USER)
	#include "glcd_user_config.h"
	#include "glcd_user_config.c"
#else

#if defined(GLCD_DEVICE_PIC24H)

#include <stdint.h>
#include <xc.h>
#include <libpic30.h>

#if defined(GLCD_CONTROLLER_PCD8544)

	/* Pin configuration for Microstick II board, PGE* switch in 'A' position */

	/**
	 * \name SPI port and pins. SPI1 port is used in \file PIC24H.c. Define
	 * the TRIS and PIN registers.
	 * @{
	 */
	#define CONTROLLER_MOSI_TRIS  _TRISB14
	#define CONTROLLER_MOSI_PIN   _LATB14
	#define CONTROLLER_SCK_TRIS   _TRISB15
	#define CONTROLLER_SCK_PIN    _LATAB15

	/* Output mapping for SPI1 (should be the same as above pins) */
	#define REGISTER_MAP_SPI_DO  _RP14R
	#define REGISTER_MAP_SPI_SCK _RP15R

	/**@}*/

	/**
	 * \name Other pins needed for serial LCD controller
	 * @{
	 */
	#define CONTROLLER_SS_TRIS   _TRISB2
	#define CONTROLLER_SS_PIN    _LATB2
	#define CONTROLLER_DC_TRIS   _TRISB3
	#define CONTROLLER_DC_PIN    _LATB3
	#define CONTROLLER_RST_TRIS  _TRISA2
	#define CONTROLLER_RST_PIN   _LATA2
	/**@}*/

#elif defined(GLCD_CONTROLLER_ST7565R)

	//#error "ST7565R not supported on PIC24H"

	/**
	 * \name SPI port and pins. SPI1 port is used in \file PIC24H.c. Define
	 * the TRIS and PIN registers.
	 * @{
	 */
	#define CONTROLLER_MOSI_TRIS  _TRISB14
	#define CONTROLLER_MOSI_PIN   _LATB14
	#define CONTROLLER_SCK_TRIS   _TRISB15
	#define CONTROLLER_SCK_PIN    _LATB15

	/* Output mapping for SPI1 (should be the same as above pins) */
	#define REGISTER_MAP_SPI_DO  _RP14R
	#define REGISTER_MAP_SPI_SCK _RP15R

	/**@}*/

	/**
	 * \name Other pins needed for serial LCD controller
	 * @{
	 */
	#define CONTROLLER_SS_TRIS   _TRISB2
	#define CONTROLLER_SS_PIN    _LATB2
	#define CONTROLLER_A0_TRIS   _TRISB3
	#define CONTROLLER_A0_PIN    _LATB3
	#define CONTROLLER_RST_TRIS  _TRISA2
	#define CONTROLLER_RST_PIN   _LATA2
	/**@}*/

#else
	#error "Controller not supported or defined in PIC24H module"
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

#endif /* GLCD_DEVICE_PIC24H */

#endif /* GLCD_DEVICE_USER */

#endif /* GLCD_PINOUTS_PIC24H_H_ */
