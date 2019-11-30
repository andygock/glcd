# glcd - Graphic LCD Library

by [Andy Gock](https://gock.net/)

## Documentation

For up to date documentation, please see the [doxygen](http://www.stack.nl/~dimitri/doxygen/) pages under the `doxygen_pages` directory and within the source code.

A online version can also be seen at:

<https://andygock.github.io/glcd-documentation/>

However the above site may not always be up to date.

## Introduction

Welcome to GLCD, an open source graphic LCD library written by [Andy Gock](https://gock.net/).

- [Author's web site](https://gock.net/)
- [GitHub repository](https://github.com/andygock/glcd)

This library has been written cleanly, to allow easy modification for use with different microcontroller devices and controller chipsets. Logic relating to devices and controllers are palced in seperate files and specific implementations can be chosen by the use of special defined symbols.

It is suitable for monochrome (black and white) LCDs with page by page data and command write style data transfer protocol. It is not compatible with color graphic LCDs.

## Features

- Draw text, of different sizes, from small 5x7 pixel fonts to large custom characters. Custom fonts can be generated using free MikroElektronika Font Creator software.
- Can write text from SRAM and Flash memory.
- Scrolling text.
- Draw vertical or horizontal bar graphs, with or without borders.
- Draw circles, lines, rectangles - filled or unfilled.
- Draw individual pixels in any color (black or white).
- Display is fully buffered, for a Nokia 5110 display of 84x48 dots, you'll need at least 504 bytes of SRAM to store the frame buffer.
- It only writes the part of the frame buffer which has changed. It does not re-write the entire buffer to the LCD every frame update.

## Supported devices

### Controllers and chipsets

Works with:

- [PCD8544](https://andygock.github.io/datasheets/philips_pcd8544.pdf) based LCDs, e.g Nokia 3110 and 5110 LCDs
- [ST7565R](https://andygock.github.io/datasheets/sitronix_st7565r.pdf) / ST7565P serial interface
- [NT75451](https://www.crystalfontz.com/controllers/Novatek/NT75451) parallel interface (used on NGX BlueBoards)

The following graphic displays have been physically tested with and confirmed working:

- NHD-C12864WC-FSW-FBW-3V3-M
- NHD-C12864A1Z-FSW-FBW-HTT
- NHD-C12832A1Z-FSW-FBW-3V3
- ZOLEN-12864-FFSSWE-NAA

### Microcontrollers

#### MCUs supported

- Atmel AVR 8-bit
- NXP LPC111x ARM Cortex-M0
- NXP LPC11Uxx ARM Cortex-M0
- ST STM32 F0 ARM Cortex-M0
- ST STM32 F4 ARM Cortex-M4
- Microchip PIC24H (and probably other 16-bit MCUs)

#### Development boards tested on (with on-board LCD)

- NGX BlueBoard LPC11U37 (with on-board NT75451 graphic LCD)

#### Development boards tested on (without on-board LCD)

- Microstick II with PIC24H and Nokia 3310/5110 LCD, ST7565R and ST7565P
- ST Nucleo F401RE

### Special note

Not all combinations of microcontroller platform and LCD controllers are supported out of the box. However you can edit the files `devices/` and `controllers/` and add your desired combination. More information on how to do this can be read in the doxygen documentation.

## Setup of symbols for compiler

The following symbols need to be defined for the compiler:

### Select microcontroller

Pick microcontroller type (pick one only):

    GLCD_DEVICE_LPX111X
    GLCD_DEVICE_LPX11UXX
    GLCD_DEVICE_AVR8
    GLCD_DEVICE_STM32F0XX
    GLCD_DEVICE_STM32F4XX
    GLCD_DEVICE_PIC24H

### Select LCD controller
Pick LCD controller type (pick one only):

    GLCD_CONTROLLER_PCD8544
    GLCD_CONTROLLER_ST7565R
    GLCD_CONTROLLER_NT75451

For ST7565P controllers, treat as ST7565R. For most if not all parts here, they behave the same way.

### Select SPI or parallel interface

If using a parallel interface LCD (e.g NT75451 on NGX BlueBoard):

    GLCD_USE_PARALLEL

When using SPI controllers:

    GLCD_USE_SPI

Note the SPI symbol isn't actually checked by the source at the moment, and it is fine if it is not used. It is for forward compatibility only. One day I may decide to check for it.

### Initialisation sequence

For the Newhaven displays using ST7565 based controllers listed above which have been tested as working, there are certain initialisation sequences which should be followed, and this may vary from display to display. To force a certain (and tested) initialisation sequence, define one of the following:

    GLCD_INIT_NHD_C12832A1Z_FSW_FBW_3V3
    GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT
    GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M
    GLCD_INIT_ZOLEN_12864_FFSSWE_NAA

If you don't specify a NHD model, ST7565 controller selection will default to `GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M` sequence. This however may change in the future.

### Reset time

To set a reset time, used by the `glcd_reset()` function, set `GLCD_RESET_TIME` to desired duration in milliseconds.

### Contrast

When using PCD8544 controllers, define a `PCD8544_CONTRAST` symbol with a 8-bit unsigned integer for the contast value. If this is not defined, a default value will be used.

### LCD dimensions

Set `GLCD_LCD_WIDTH` and `GLCD_LCD_HEIGHT` to define custom LCD dimensions. If these are not user defined, then a default width and height is used. The default dimensions are 128x64 except for PCD8544 controllers which is 84x48.

### Compiler setup

These symbols need to be set in the configuration options of your IDE, usually in the "defined symbols" section, or they can be defined in a makefile as `-D` options.

Example:

    -DGLCD_DEVICE_LPC111X

### Delay Timing

Some operations such as sending a reset pulse, requires the use of a delay timer. The library will refer to a external function called `delay_ms(t)` where t is the delay required in milliseconds. Please ensure you have this function elsewhere in your program.

#### AVR devices

If you are using avr-gcc with Atmel devices, you can force the library to use the built-in `_delay_ms()` function by setting the compiler symbols:

    GLCD_USE_AVR_DELAY
    __DELAY_BACKWARD_COMPATIBLE__

`F_CPU` must be set to your clock frequency for the above [AVR built-in delay](http://www.nongnu.org/avr-libc/user-manual/group__util__delay.html) routine to work.

## Sample applications and videos

- STM32F0 Discovery with PCD8544 Nokia 5110 LCD - [Download](https://andygock.github.io/glcd-samples/GLCD_STM32F0_PCD8544.zip) Keil MDK project
- Custom PCB with Atmel ATMEGA2560 and ST7565R Newhaven 128×64 display - [Download](https://andygock.github.io/glcd-samples/as6_mega2560_st7565r.zip) Atmel Studio 6 project
- Atmel AT90USBKEY board with PCD8544 Nokia 5110 LCD - [Download](https://andygock.github.io/glcd-samples/glcd-example-at90usbkey-avrstudio.zip) Atmel Studio 5 project
- ZERO Z111xP Cortex-M0 LPC1114 board with PCD8544 Nokia 5110 LCD - [Download](https://andygock.github.io/glcd-samples/glcd-example-LPC1114-CooCox.zip) CooCox CoIDE project or watch [video](http://www.youtube.com/watch?v=mWsTbLW5Hm4)
- NGX LPC11U37 BlueBoard with built in NT75451 parallel chipset LCD - [Download](https://andygock.github.io/glcd-samples/glcd-example-LPC11U37-BlueBoard-Keil.zip) Keil MDK project
- Microstick II development board, with PIC24H and Newhaven ST7565R display NHD-C12864A1Z-FSW-FBW-HTT - [Download](https://andygock.github.io/glcd-samples/demo-microstick_PIC24HJ128_ST7565R.zip) MPLAB X project or watch [video](http://www.youtube.com/watch?v=1ocUWbEOs5Y)
- Microstick II development board, with PIC24H and Newhaven ST7565P display NHD-C12832A1Z-FSW-FBW-3V3 - [Download](https://andygock.github.io/glcd-samples/demo-microstick_PIC24HJ128_ST7565P.zip) MPLAB X project or watch [video](http://www.youtube.com/watch?v=j7bQ-8SIgYc)
- Microstick II development board, with PIC24H and PCD8544 Nokia 5110 display - [Download](https://andygock.github.io/glcd-samples/demo-microstick_PIC24HJ128_PCD8544.zip) MPLAB X project
- Pinguino development board, with PIC32MX440F256H and PCD8544 Nokia 5110 display - [Download](https://andygock.github.io/glcd-samples/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.zip) MPLAB X project (Thanks to [Joris Putcuyps](https://github.com/jputcu))

The code samples above will have the glcd library code already inside it, however I haven’t made any attempt to keep the glcd library updated in the examples so I advise that if you are using the example code, to replace the glcd directory (usually in `library/glcd` or `lib/glcd`) with the latest updated code.

## Display bitmap images

Bitmap images can be converted into a byte array using [LCD Assistant](http://en.radzio.dxp.pl/bitmap_converter/)

When using this software, we need to set 8 pixels per byte with vertical byte orientation. Do not include size.
