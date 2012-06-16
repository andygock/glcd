/**
   \file glcd_devices.h
   \brief Functions specific to certain devices.
          These are functions are defined in devices/xxxx.c
   \author Andy Gock
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

#ifndef GLCD_DEVICES_H_
#define GLCD_DEVICES_H_

#if defined(GLCD_DEVICE_AVR8)
	#include <avr/io.h>
#elif defined(GLCD_DEVICE_LPC111X)
	#include <LPC11xx.h>
#else
	#error "Device not supported"
#endif

/** \addtogroup Devices 
Device specific functions.
Currently only the following devices are supported:
- Atmel 8-bit AVR

The following is planned to be supported in the near future:
- Atmel 32-bit AVR
- NXP LPC1xxx ARM Cortex-M0
@{ */

/** Initialise the LCD. This function is platform and controller specific. */
void glcd_init(void);

/** Write a byte to the connected SPI slave. (AVR8 only)*/
void glcd_spi_write(uint8_t c);

/** Reset the LCD. */
void glcd_reset(void);

/** @}*/

#endif /* GLCD_DEVICES_H_ */
