/** Unit Tests
 *  \author Andy Gock
 *
 */

#include "glcd.h"
#include "unit_tests.h"

/** Fonts */
#include "library/glcd/fonts/font5x7.h"
//#include "library/glcd/fonts/Bebas_Neue20x36_Bold_Numbers.h"
//#include "library/glcd/fonts/Liberation_Sans27x36_Numbers.h"
#include "library/glcd/fonts/HelveticaNeueLT_Com_57_Cn23x35_Numbers.h"

void glcd_test_circles(void)
{
	while (1) {
		glcd_clear();
		for (uint8_t i=0; i<=20; i++) {
			glcd_fill_circle(20,20,i,BLACK);
			glcd_write();
			_delay_ms(2);
		}
		for (uint8_t i=0; i<=20; i++) {
			glcd_fill_circle(20,20,i,WHITE);
			glcd_write();
			_delay_ms(2);
		}
	}
}

void glcd_test_counter_and_graph(void)
{
	uint8_t count = 0;
	char string[8] = "";
	while(1) {
		glcd_clear_buffer();

		//glcd_tiny_set_font(Font5x7,5,7,32,127);
		//glcd_draw_string_xy(0,40,(char *)utoa(count,string,10));

		//glcd_set_font(Liberation_Sans15x21_Numbers,15,21,46,57);
		//glcd_set_font(Liberation_Sans27x36_Numbers,27,36,46,57);
		//glcd_set_font(Bebas_Neue20x36_Bold_Numbers,20,36,46,57);
		//glcd_set_font(Bebas_Neue18x36_Numbers,18,36,46,57);
		glcd_set_font(HelveticaNeueLT_Com_57_Cn23x35_Numbers,23,35,46,57);

		sprintf(string,"%d",count);
		glcd_draw_string_xy(0,0,string);
		glcd_bar_graph_horizontal(10,38,30,6,count*4);
		glcd_bar_graph_vertical(70,0,8,30,count*2);

		glcd_write();
		count += 1;

	}

}

void glcd_test_tiny_up_down(void)
{
	uint8_t x,y;

	glcd_tiny_set_font(Font5x7,5,7,32,127);

	while(1) {

		for (y=0; y<43; y++) {
			glcd_clear_buffer();
			glcd_draw_string_xy(0,y,"DOWN");
			glcd_write();
			_delay_ms(100);
		}

		for (y=0; y<43; y++) {
			glcd_clear_buffer();
			glcd_draw_string_xy(0,42-y,"UP");
			glcd_write();
			_delay_ms(100);
		}

	}

}
