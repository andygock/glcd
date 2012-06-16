/**
 * Pinouts for Atmel 8-bit AVR MCUs
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
		* Neither the name of the copyright holders nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
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
	
// ports and pins used
#define PCD8544_MOSI_PORT PORTB
#define PCD8544_MOSI_PIN  2
#define PCD8544_MISO_PORT PORTB
#define PCD8544_MISO_PIN  3
#define PCD8544_SCK_PORT  PORTB
#define PCD8544_SCK_PIN   1
#define PCD8544_SS_PORT   PORTB
#define PCD8544_SS_PIN    0
#define PCD8544_DC_PORT   PORTB
#define PCD8544_DC_PIN    5
#define PCD8544_RST_PORT  PORTB
#define PCD8544_RST_PIN   4

#define GLCD_SELECT()     cbi(PCD8544_SS_PORT,PCD8544_SS_PIN)
#define GLCD_DESELECT()   sbi(PCD8544_SS_PORT,PCD8544_SS_PIN)
#define GLCD_DC_LOW()     cbi(PCD8544_DC_PORT,PCD8544_DC_PIN)
#define GLCD_DC_HIGH()    sbi(PCD8544_DC_PORT,PCD8544_DC_PIN)
#define GLCD_RESET_LOW()  cbi(PCD8544_RST_PORT,PCD8544_RST_PIN)
#define GLCD_RESET_HIGH() sbi(PCD8544_RST_PORT,PCD8544_RST_PIN)

#endif

#endif /* GLCD_PINOUTS_AVR8_H_ */
