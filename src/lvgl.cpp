#include "lvgl.h"
#include <cstdlib>

void lv_init(void) {}

void lv_disp_draw_buf_init(lv_disp_draw_buf_t* draw_buf, lv_color_t* buf1,
                           lv_color_t* buf2, uint32_t size) {
    draw_buf->buf1 = buf1;
    draw_buf->buf2 = buf2;
    draw_buf->size = size;
}

void lv_disp_drv_init(lv_disp_drv_t* drv) {
    drv->flush_cb = nullptr;
    drv->draw_buf = nullptr;
    drv->user_data = nullptr;
    drv->hor_res = 0;
    drv->ver_res = 0;
}

lv_disp_t* lv_disp_drv_register(lv_disp_drv_t* drv) {
    (void)drv;
    return static_cast<lv_disp_t*>(std::malloc(sizeof(lv_disp_t)));
}

void lv_timer_handler(void) {}
