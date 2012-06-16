/**
 *
 */

#ifndef _UNIT_TESTS_H
#define _UNIT_TESTS_H

#if defined(GLCD_DEVICE_LPC111X)
	extern void delay_ms(uint32_t ms);
	#define PROGMEM
	#define _delay_ms(t) delay_ms(t)
#endif

void glcd_test_circles(void);
void glcd_test_counter_and_graph(void);
void glcd_test_tiny_up_down(void);

#endif
