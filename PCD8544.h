/**
 * \file PCD8544.h
 * \brief PCD8544 LCD Library
 * \author Andy Gock
 *
 */ 

#ifndef _PCD8544_H
#define _PCD8544_H

#if defined(PCD8544_DEVICE_AVR8)
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
	
// pins used
#define PCD8544_MOSI_PORT  PORTB
#define PCD8544_MOSI_PIN   2
#define PCD8544_MISO_PORT  PORTB
#define PCD8544_MISO_PIN   3
#define PCD8544_SCK_PORT  PORTB
#define PCD8544_SCK_PIN   1
#define PCD8544_SS_PORT  PORTB
#define PCD8544_SS_PIN   0
#define PCD8544_DC_PORT  PORTB
#define PCD8544_DC_PIN   5
#define PCD8544_RST_PORT PORTB
#define PCD8544_RST_PIN  4

#define PCD8544_SELECT()     cbi(PCD8544_SS_PORT,PCD8544_SS_PIN)
#define PCD8544_DESELECT()   sbi(PCD8544_SS_PORT,PCD8544_SS_PIN)
#define PCD8544_DC_LOW()     cbi(PCD8544_DC_PORT,PCD8544_DC_PIN)
#define PCD8544_DC_HIGH()    sbi(PCD8544_DC_PORT,PCD8544_DC_PIN)
#define PCD8544_RESET_LOW()  cbi(PCD8544_RST_PORT,PCD8544_RST_PIN)
#define PCD8544_RESET_HIGH() sbi(PCD8544_RST_PORT,PCD8544_RST_PIN)

#else
	#error "Device not supported"
#endif

#define BLACK 1
#define WHITE 0

#define PCD8544_LCD_WIDTH 84
#define PCD8544_LCD_HEIGHT 48

// instruction set bit masks

#define PCD8544_NOP 0

// function set commands
#define PCD8544_FUNCTION_SET          (1<<5)
#define PCD8544_POWER_DOWN            (1<<2)
#define PCD8544_HORIZONTAL_ADDRESSING 0
#define PCD8544_VERTICAL_ADDRESSING   (1<<1)
#define PCD8544_EXTENDED_INSTRUCTION  (1<<0)

// H=0 (basic instruction set)
#define PCD8544_DISPLAY_CONTROL  (1<<3)
#define PCD8544_DISPLAY_BLANK    0x0
#define PCD8544_DISPLAY_NORMAL   (1<<2)
#define PCD8544_DISPLAY_ALL_ON   (1<<0)
#define PCD8544_DISPLAY_INVERTED (1<<2|1<<0)

#define PCD8544_SET_Y_ADDRESS       0x40
#define PCD8544_SET_X_ADDRESS       0x80


// H=1 (extended instruction set)
#define PCD8544_SET_TEMP (1<<2)
#define PCD8544_TEMPCO_0 0b00
#define PCD8544_TEMPCO_1 0b01
#define PCD8544_TEMPCO_2 0b10
#define PCD8544_TEMPCO_3 0b11

#define PCD8544_SET_BIAS (1<<4)
#define PCD8544_SET_VOP  (1<<7)

//
#define PCD8544_MAX_BANKS 6
#define PCD8544_MAX_COLS  84

//
typedef struct {
	uint8_t x_min;
	uint8_t y_min;
	uint8_t x_max;
	uint8_t y_max;
} PCD8544_BoundingBox_t;

// platform specific functions

/** Initialise the PCD8544 chip. This function is platform specific. Currently only supports 8-bit AVRs. */
void PCD8544_init(void);

/** Write a byte to the connected SPI slave, in this case, it is the PCD8544. */
void PCD8544_spi_write(uint8_t c);

/** Reset the PCD8544. */
void PCD8544_reset(void);

/** Send command byte to LCD. */
void PCD8544_command(uint8_t c);

/** Send data byte to LCD. */
void PCD8544_data(uint8_t c);

/** Set contrast (Vop) from 0 to 127. This should be experimentally determined. */
void PCD8544_set_contrast(uint8_t val);

/** Power up the device. */
void PCD8544_power_down(void);

/** Power down the device. */
void PCD8544_power_up(void);

/** Set Y address of RAM (select bank). Device must be under basic instruction set mode before using this.
 *  \param y Y address of RAM (0 <= Y <= 5)
 */
void PCD8544_set_y_address(uint8_t y);

/** Set X address of RAM (column). Device must be under basic instruction set mode before using this.
 *  \param y X address of RAM (0 <= X <= 83)
 */
void PCD8544_set_x_address(uint8_t x);

/** Update the display within the specified bounding box. This physically writes data to the PCD8544's RAM. */
void PCD8544_write();
void PCD8544_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax);
void PCD8544_reset_bbox();

/** Clear the display. This will clear the buffer and physically write and commit it to the LCD */
void PCD8544_clear(void);

/** Clear the display buffer only. This does not physically write the changes to the LCD */
void PCD8544_clear_buffer(void);
void PCD8544_select_screen(uint8_t *buffer, PCD8544_BoundingBox_t *bbox);
void PCD8544_scroll(int8_t x, int8_t y);
void PCD8544_scroll_line(void);

// graphics

void PCD8544_set_pixel(uint8_t x, uint8_t y, uint8_t color);
uint8_t PCD8544_get_pixel(uint8_t x, uint8_t y);
void PCD8544_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void PCD8544_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void PCD8544_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void PCD8544_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
void PCD8544_fill_circle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

// text

enum font_table_type { STANG, MIKRO };

typedef struct {
	const char *font_table;
	uint8_t width;
	uint8_t height;
	char start_char;
	char end_char;
	enum font_table_type table_type;
} PCD8544_FontConfig_t;

/** Set font to be used from now on. This is the tiny 5x7 monospace font.
 *  \param font_table flash pointer to start from font table
 *  \param width      width of each character
 *  \param height     height of each character
 *  \param start_char start character
 *  \param end_char   end character
 */
void PCD8544_tiny_set_font(const char *font_table, uint8_t width, uint8_t height, char start_char, char end_char);

/** Write character to LCD in tiny 5x7 font.
 *  \param x    column position to start 
 *  \param line line number to be written (each line is 8 pixels high)
 *  \param str  string to be written
 */
void PCD8544_tiny_draw_char(uint8_t x, uint8_t line, char c);

/** Write string to display buffer in tiny 5x7 font.
 *  Will wrap to next line if needed. Screen is not updated. Use PCD8544_write() to physically update display.
 *  \param x    column position to start 
 *  \param line line number to be written (each line is 8 pixels high)
 *  \param str  string to be written
 */
void PCD8544_tiny_draw_string(uint8_t x, uint8_t line, char *str);

/** Write flash string to display buffer in tiny 5x7 font.
 *  Will wrap to next line if needed. Screen is not updated. Use PCD8544_write() to physically update display.
 *  \param x    column position to start 
 *  \param line line to be written (each line is 8 pixels high)
 *  \param str  string stored in flash memory to be written
 */
void PCD8544_tiny_draw_string_P(uint8_t x, uint8_t line, const char *str);

/** Write string to bottom row of display.
 *  Screen buffer is scrolled up by one line. Screen is then physically updated.
 *  \param str string to be written
 */
void PCD8544_tiny_draw_string_ammend(char *str);

/** Write string from flash memory to bottom row of display.
 *  Screen buffer is scrolled up by one line. Screen is then physically updated.
 *  \param str string to be written
 */
void PCD8544_tiny_draw_string_ammend_P(const char *str);

#define PCD_WRITE(str)   PCD8544_tiny_draw_string_ammend(str)
#define PCD_WRITE_P(str) PCD8544_tiny_draw_string_ammend_P(str)

void PCD8544_set_font(PGM_P font_table, uint8_t width, uint8_t height, char start_char, char end_char);
uint8_t PCD8544_draw_char_xy(uint8_t x, uint8_t y, char c);
void PCD8544_draw_string_xy(uint8_t x, uint8_t y, char *c);
void PCD8544_draw_string_xy_P(uint8_t x, uint8_t y, const char *str);

#endif