#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <bcm2835.h>

#include "glcd.h"
#include "fonts/font5x7.h"


int main(int argc, char* const argv[])
{

    struct sched_param sp;
    memset(&sp, 0, sizeof(sp));
    sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &sp);
    mlockall(MCL_CURRENT | MCL_FUTURE);

    glcd_tiny_set_font(Font5x7, 5, 7, 32, 127);
    glcd_select_screen((uint8_t *)&glcd_buffer, &glcd_bbox);

    if (glcd_init() > 0) {
        printf("glcd_init error!");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    glcd_normal();
    glcd_clear_buffer();
    glcd_tiny_draw_string(4, 2, " #/***/#");
    glcd_tiny_draw_string(4, 3, " #|^_^|# Hello World!");
    glcd_tiny_draw_string(4, 4, " #/---/#  By HanChen");
    glcd_write();
    bcm2835_delay(1000 * 30);

    // Relative positioning
    glcd_clear_buffer();
    glcd_fill_rect(4, 0, 127, 63, 1);
    glcd_fill_rect(4, 0, 1, 1, 0);
    glcd_fill_rect(131, 0, 1, 1, 1);
    glcd_fill_rect(4, 63, 1, 1, 1);
    glcd_fill_rect(131,63, 1, 1, 1);
    glcd_write();
    bcm2835_delay(1000 * 1);
    glcd_close();
    exit(EXIT_SUCCESS);
}


