/**
 * Pinouts for Atmel 8-bit AVR MCUs
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