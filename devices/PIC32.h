#ifndef GLCD_PINOUTS_PIC32_H_
#define GLCD_PINOUTS_PIC32_H_

#if defined(GLCD_DEVICE_USER)
	#include "glcd_user_config.h"
	#include "glcd_user_config.c"
#else

#if defined(GLCD_DEVICE_PIC32)

#include <stdint.h>
#include <xc.h>
#include <plib.h>

#if defined(GLCD_CONTROLLER_PCD8544)
        // * Chipselect            -> UEXT PIN 10 -> RF0
        #define LCD_CS_PORT           IOPORT_F
        #define LCD_CS_PIN            BIT_0
        // * D/C (data/command)    -> UEXT PIN 6 -> Arduino A4  ->  RD9
        #define LCD_DC_RESET_PORT     IOPORT_D
        #define LCD_DC_PIN            BIT_9
        // * LCD RESET(active low) -> UEXT PIN 5 -> Arduino A5  ->  RD10
        #define LCD_RESET_PIN         BIT_10
#else
	#error "Controller not supported or defined in PIC32 module"
#endif

/**
 * \name Macros for control lines
 * @{
 */
#define GLCD_SELECT()     PORTClearBits(LCD_CS_PORT, LCD_CS_PIN)
#define GLCD_DESELECT()   PORTSetBits(LCD_CS_PORT, LCD_CS_PIN)
#define GLCD_DC_LOW()     PORTClearBits(LCD_DC_RESET_PORT, LCD_DC_PIN)
#define GLCD_DC_HIGH()    PORTSetBits(LCD_DC_RESET_PORT, LCD_DC_PIN)
#define GLCD_RESET_LOW()  PORTClearBits(LCD_DC_RESET_PORT, LCD_RESET_PIN)
#define GLCD_RESET_HIGH() PORTSetBits(LCD_DC_RESET_PORT, LCD_RESET_PIN)
/**@}*/

#endif /* GLCD_DEVICE_PIC32 */

#endif /* GLCD_DEVICE_USER */

#endif /* GLCD_PINOUTS_PIC32_H_ */
