glcd - Graphic LCD Library
==========================

by Andy Gock

Supported Devices
-----------------

Works with:
- PCD8544 based LCDs, e.g Nokia 3110 and 5110 LCDs
- ST7565R serial interface (used in Newhaven Display NHD-C12864WC-FSW-FBW-3V3-M)
- NT75451 parallel interface (used on NGX BlueBoards)

MCUs supported:
- Atmel AVR 8-bit
- NXP LPC111x ARM Cortex-M0
- NXP LPC11Uxx ARM Cortex-M0
- ST STM32 F0 ARM Cortex-M0

Development boards tested on:
- NGX BlueBoard LPC11U37 (with NT75451 graphic LCD)

Setup of symbols for compiler
-----------------------------

The following symbols need to be set for the compiler:

Pick microcontroller type (pick one only):

	GLCD_DEVICE_LPX111X
	GLCD_DEVICE_LPX11UXX
	GLCD_DEVICE_AVR8
	GLCD_DEVICE_STM32F0XX

Pick LCD controller type (pick one only):

	GLCD_CONTROLLER_PCD8544
	GLCD_CONTROLLER_ST7565R
	GLCD_CONTROLLER_NT75451

If using a parallel interface LCD (e.g NT75451 on NGX BlueBoard):

	GLCD_USE_PARALLEL

When using SPI controllers:

	GLCD_USE_SPI

Note the SPI symbol isn't checked, and it is fine if it is not used.
It is for forward compatibility only.

To set a reset time, used by the glcd_reset() function, set GLCD_RESET_TIME to desired duration in milliseconds.

These symbols need to be set in the configuration options of your IDE, usually
in the "defined symbols" section, or they can be defined in a makefile
as -D options.

Example:

	-DGLCD_DEVICE_LPC111X

Delay Timing
------------

Some operations such as sending a reset pulse, requires the use of a delay timer. The library will refer to a
external function called delay_ms(t) where t is the delay required in milliseconds. Please ensure you have
this function elsewhere in your program.

If you are using avr-gcc with Atmel devices, you can force the library to use the built-in _delay_ms() function
by setting the compiler symbols:

	GLCD_USE_AVR_DELAY
	__DELAY_BACKWARD_COMPATIBLE__
	
Documentation
-------------

Refer to Doxygen generated pages for detailed documentation. You'll need to generate the documentation yourself,
simply install Doxygen and load the doxygen file in the root directory of the library and generate the documents
in a file format of your choice (HTML, PDF, TEX etc).

