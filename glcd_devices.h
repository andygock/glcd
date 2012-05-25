/**
   \file glcd_devices.h
   \brief Functions specific to certain devices.
          These are functions are defined in devices/xxxx.c
   \author Andy Gock
 */ 


#ifndef GLCD_DEVICES_H_
#define GLCD_DEVICES_H_

#if defined(GLCD_DEVICE_AVR8)
#include <avr/io.h>
#else

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