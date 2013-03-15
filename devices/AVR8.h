/**
 * \file AVR8.h
 * \brief Pinouts to Atmel AVR 8-bit AVRs.
 * \author Andy Gock
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

#ifndef GLCD_PINOUTS_AVR8_H_
#define GLCD_PINOUTS_AVR8_H_

#if defined(GLCD_DEVICE_AVR8)

#include <avr/io.h>
#include <avr/pgmspace.h>

#ifndef _BITHELPERS_
#define _BITHELPERS_
#define sbi(var, mask)   ((var) |= _BV(mask))
#define cbi(var, mask)   ((var) &= ~(_BV(mask)))
#define DDR(x) (*(&x - 1))
#define PIN(x) (*(&x - 2)) 
#endif

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#if defined(GLCD_CONTROLLER_PCD8544)
	
	/**
	 * \name SPI port and pins
	 * @{
	 */
	#define AVR_SS_PORT          PORTB
	#define AVR_SS_PIN           0		
	#define CONTROLLER_MOSI_PORT PORTB
	#define CONTROLLER_MOSI_PIN  2
	#define CONTROLLER_MISO_PORT PORTB
	#define CONTROLLER_MISO_PIN  3
	#define CONTROLLER_SCK_PORT  PORTB
	#define CONTROLLER_SCK_PIN   1
	/**@}*/

	/**
	 * \name Other pins needed for serial LCD controller
	 * @{
	 */
	#define CONTROLLER_SS_PORT   PORTA
	#define CONTROLLER_SS_PIN    5
	#define CONTROLLER_DC_PORT   PORTB
	#define CONTROLLER_DC_PIN    5
	#define CONTROLLER_RST_PORT  PORTB
	#define CONTROLLER_RST_PIN   4
	/**@}*/

#elif defined (GLCD_CONTROLLER_ST7565R)
	/**
	 * \name SPI port and pins
	 * @{
	 */
	#define AVR_SS_PORT          PORTB
	#define AVR_SS_PIN           0	
	#define CONTROLLER_MOSI_PORT PORTB
	#define CONTROLLER_MOSI_PIN  2
	#define CONTROLLER_MISO_PORT PORTB
	#define CONTROLLER_MISO_PIN  3
	#define CONTROLLER_SCK_PORT  PORTB
	#define CONTROLLER_SCK_PIN   1
	/**@}*/

	/**
	 * \name Other pins needed for serial LCD controller
	 * @{
	 */
	#define CONTROLLER_A0_PORT   PORTC /**< Output port to GLCD A0 pin. */
	#define CONTROLLER_A0_PIN    0     /**< Output pin number to GLCD A0 pin. */	
	#define CONTROLLER_SS_PORT   PORTG
	#define CONTROLLER_SS_PIN    0
	#define CONTROLLER_RST_PORT  PORTG
	#define CONTROLLER_RST_PIN   1
	/**@}*/
#else
	#error "Controller not supported by AVR8"
#endif

/**
 * \name Macros for control lines
 * @{
 */
#define GLCD_SELECT()     cbi(CONTROLLER_SS_PORT,CONTROLLER_SS_PIN)
#define GLCD_DESELECT()   sbi(CONTROLLER_SS_PORT,CONTROLLER_SS_PIN)
#define GLCD_DC_LOW()     cbi(CONTROLLER_DC_PORT,CONTROLLER_DC_PIN)
#define GLCD_DC_HIGH()    sbi(CONTROLLER_DC_PORT,CONTROLLER_DC_PIN)
#define GLCD_RESET_LOW()  cbi(CONTROLLER_RST_PORT,CONTROLLER_RST_PIN)
#define GLCD_RESET_HIGH() sbi(CONTROLLER_RST_PORT,CONTROLLER_RST_PIN)

#define GLCD_A0_LOW()     cbi(CONTROLLER_A0_PORT,CONTROLLER_A0_PIN)
#define GLCD_A0_HIGH()    sbi(CONTROLLER_A0_PORT,CONTROLLER_A0_PIN)

/**@}*/

#endif

#endif /* GLCD_PINOUTS_AVR8_H_ */
