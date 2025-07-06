#ifndef LVGL_H
#define LVGL_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t lv_color_t;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} lv_area_t;

typedef struct {
    lv_color_t* buf1;
    lv_color_t* buf2;
    uint32_t size;
} lv_disp_draw_buf_t;

typedef struct lv_disp_drv_t {
    void (*flush_cb)(struct lv_disp_drv_t*, const lv_area_t*, lv_color_t*);
    lv_disp_draw_buf_t* draw_buf;
    void* user_data;
    int hor_res;
    int ver_res;
} lv_disp_drv_t;

typedef struct {
    lv_disp_drv_t* driver;
} lv_disp_t;

void lv_init(void);
void lv_disp_draw_buf_init(lv_disp_draw_buf_t* draw_buf, lv_color_t* buf1,
                           lv_color_t* buf2, uint32_t size);
void lv_disp_drv_init(lv_disp_drv_t* drv);
lv_disp_t* lv_disp_drv_register(lv_disp_drv_t* drv);
void lv_timer_handler(void);

#ifdef __cplusplus
}
#endif

#endif // LVGL_H
