glcd - Graphic LCD Library
==========================

by Andy Gock

Up to date documentation
------------------------

For up to date documentation, please see the doxygen pages under the `doxygen_pages` directory.

A online version can also be seen at:

http://s.agock.com/glcd-documentation

However this site may not always be kept up to date.

Introduction
============

Welcome to GLCD, an open source graphic LCD library written by Andy Gock.

Author's web site: http://agock.com/

GitHub repository: https://github.com/andygock/glcd

This library has been written cleanly, to allow easy modification for use with different microcontroller devices and controller chipsets. Logic relating to devices and controllers are palced in seperate files and specific implementations can be chosen by the use of special defined symbols.

It is suitable for monochrome (black and white) LCDs with page by page data and command write style data transfer protocol. It is not suitable for color graphic LCDs.

Supported controllers and chipsets
----------------------------------

Works with:

- PCD8544 based LCDs, e.g Nokia 3110 and 5110 LCDs
- ST7565R / ST7565P serial interface
- NT75451 parallel interface (used on NGX BlueBoards)

The following Newhaven displays have been physically tested with and confirmed working:

- NHD-C12864WC-FSW-FBW-3V3-M
- NHD-C12864A1Z-FSW-FBW-HTT
- NHD-C12832A1Z-FSW-FBW-3V3
- ZOLEN-12864-FFSSWE-NAA

Supported microcontrollers
--------------------------

MCUs supported:

- Atmel AVR 8-bit
- NXP LPC111x ARM Cortex-M0
- NXP LPC11Uxx ARM Cortex-M0
- ST STM32 F0 ARM Cortex-M0
- ST STM32 F4 ARM Cortex-M4
- Microchip PIC24H (and probably other 16-bit MCUs)

Development boards tested on (with on-board LCD):

- NGX BlueBoard LPC11U37 (with on-board NT75451 graphic LCD)

Development boards tested on (without on-board LCD):

- Microstick II with PIC24H and Nokia 3310/5110 LCD, ST7565R and ST7565P
- ST Nucleo F401RE.

### Special note

Not all combinations of microcontroller platform and LCD controllers are supported out of the box. However you can edit the files `devices/` and `controllers/` and add your desired combination. More information on how to do this can be read in the doxygen documentation.

Setup of symbols for compiler
-----------------------------

The following symbols need to be defined for the compiler:

Pick microcontroller type (pick one only):

	GLCD_DEVICE_LPX111X
	GLCD_DEVICE_LPX11UXX
	GLCD_DEVICE_AVR8
	GLCD_DEVICE_STM32F0XX
	GLCD_DEVICE_STM32F4XX
	GLCD_DEVICE_PIC24H

Pick LCD controller type (pick one only):

	GLCD_CONTROLLER_PCD8544
	GLCD_CONTROLLER_ST7565R
	GLCD_CONTROLLER_NT75451

For ST7565P controllers, treat as ST7565R. For most if not all parts here, they behave the same way.

If using a parallel interface LCD (e.g NT75451 on NGX BlueBoard):

	GLCD_USE_PARALLEL

When using SPI controllers:

	GLCD_USE_SPI

Note the SPI symbol isn't actually checked by the source at the moment, and it is fine if it is not used. It is for forward compatibility only. One day I may decide to check for it.

For the Newhaven displays using ST7565 based controllers listed above which have been tested as working, there
are certain initialisation sequences which should be followed, and this may vary
from display to display. To force a certain (and tested) initialisation
sequence, define one of the following:

	GLCD_INIT_NHD_C12832A1Z_FSW_FBW_3V3
	GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT
	GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M
	GLCD_INIT_ZOLEN_12864_FFSSWE_NAA

If you don't specify a NHD model, ST7565 controller selection will default to `GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M` sequence.
This however may change in the future.

To set a reset time, used by the `glcd_reset()` function, set `GLCD_RESET_TIME` to desired duration in milliseconds.

These symbols need to be set in the configuration options of your IDE, usually
in the "defined symbols" section, or they can be defined in a makefile
as `-D` options.

Example:

	-DGLCD_DEVICE_LPC111X

Delay Timing
------------

Some operations such as sending a reset pulse, requires the use of a delay timer. The library will refer to a
external function called `delay_ms(t)` where t is the delay required in milliseconds. Please ensure you have
this function elsewhere in your program.

If you are using avr-gcc with Atmel devices, you can force the library to use the built-in `_delay_ms()` function
by setting the compiler symbols:

	GLCD_USE_AVR_DELAY
	__DELAY_BACKWARD_COMPATIBLE__
	
Documentation
-------------

Refer to Doxygen generated pages for detailed documentation. You'll can generate the documentation yourself,
simply install Doxygen and load the doxygen file in the root directory of the library and generate the documents
in a file format of your choice (HTML, PDF, TEX etc).

There is also a online version (link at top of this document)
