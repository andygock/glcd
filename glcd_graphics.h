/**
   \file glcd_graphics.h
   \brief 
   \author Andy Gock
 */ 


#ifndef GLCD_GRAPHICS_H_
#define GLCD_GRAPHICS_H_

#if defined(GLCD_DEVICE_AVR8)
#include <avr/io.h>
#else

#endif

/** \addtogroup Graphics
 *  Graphics specific functions
 *  @{
 */

void glcd_set_pixel(uint8_t x, uint8_t y, uint8_t color);
uint8_t glcd_get_pixel(uint8_t x, uint8_t y);
void glcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void glcd_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void glcd_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void glcd_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
void glcd_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

/** @}*/

#endif /* GLCD_GRAPHICS_H_ */