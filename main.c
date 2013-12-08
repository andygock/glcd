#include <stdio.h>
#include <bcm2835.h>
#include <string.h>
#include <sched.h>
#include <sys/mman.h>
#include "glcd.h"
#include "fonts/font5x7.h"


int main(int argc, char* const argv[])
{

    struct sched_param sp;
    memset(&sp, 0, sizeof(sp));
    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &sp);
    mlockall(MCL_CURRENT | MCL_FUTURE);

    if (glcd_init() > 0){
        printf("glcd_init error!");
    }
    glcd_tiny_set_font(Font5x7, 5, 7, 32, 127);
    fflush(stdout);
    glcd_all_on();
    bcm2835_delay(1000 * 1);
    glcd_normal();
    bcm2835_delay(1000 * 5);
    glcd_pattern();
    bcm2835_delay(1000 * 5);
    glcd_select_screen(&glcd_buffer, &glcd_bbox);
    glcd_clear_buffer();
    glcd_tiny_draw_string(10,10,"Hello World!");
    glcd_write();
    bcm2835_delay(1000 * 10);
    glcd_close();
    return 0;
}


