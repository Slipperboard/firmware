#include "dummy_device.h"
#include <stdio.h>

static esp_err_t dummy_init(hal_device_t *dev)
{
    (void)dev;
    printf("Dummy device initialized\n");
    return ESP_OK;
}

static esp_err_t dummy_deinit(hal_device_t *dev)
{
    (void)dev;
    printf("Dummy device deinitialized\n");
    return ESP_OK;
}

static hal_device_ops_t dummy_ops = {
    .init = dummy_init,
    .deinit = dummy_deinit,
};

hal_device_t dummy_device = {
    .name = "dummy",
    .ops = &dummy_ops,
    .ctx = NULL,
};
