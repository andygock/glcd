/**
   \file glcd_devices.h
   \brief Functions specific to certain devices (microcontrollers).
          These are functions are defined in devices/yourdevice.c
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

#ifndef GLCD_DEVICES_H_
#define GLCD_DEVICES_H_

#if defined(GLCD_DEVICE_AVR8)
	#include <avr/io.h>
#elif defined(GLCD_DEVICE_LPC111X)
	#include "LPC11xx.h"
#elif defined(GLCD_DEVICE_LPC11UXX)
	#include "LPC11Uxx.h"
#elif defined(GLCD_DEVICE_STM32F0XX)
	#include "STM32F0xx.h"
#elif defined(GLCD_DEVICE_STM32F4XX)
	#include "stm32f4xx.h"
	#include "devices/STM32F4.h"
#elif defined(GLCD_DEVICE_PIC24H)
	#include <stdint.h>
	#include <xc.h>
	#include <libpic30.h>
#elif defined(GLCD_DEVICE_PIC32)
#else
	#error "Device not supported or defined"
#endif

/** \addtogroup Devices Devices
 *  Functions specific to certain devices (microcontrollers)
 *  \{
 */

/**
 * Initialise the LCD. This function is platform and controller specific.
 */
void glcd_init(void);

#if !defined(GLCD_USE_PARALLEL)

	/**
	 * Write a byte to the connected SPI slave.
	 * \param c Byte to be written
	 * \return Returned value from SPI (often not used)
	 */
	void glcd_spi_write(uint8_t c);

#else
	/* must be GLCD_USE_SPI */
	void glcd_parallel_write(uint8_t c);

#endif

/**
 *  Reset the LCD.
 *  \note Not all LCD controllers support reset.
 */
void glcd_reset(void);

/** @}*/

#endif /* GLCD_DEVICES_H_ */
