#ifndef HAL_HAL_H
#define HAL_HAL_H

#include <esp_err.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_MAX_DEVICES 8

typedef struct hal_device hal_device_t;

typedef struct {
    esp_err_t (*init)(hal_device_t *dev);
    esp_err_t (*deinit)(hal_device_t *dev);
} hal_device_ops_t;

struct hal_device {
    const char *name;
    const hal_device_ops_t *ops;
    void *ctx;
};

esp_err_t hal_register_device(hal_device_t *dev);
esp_err_t hal_init(void);
esp_err_t hal_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // HAL_HAL_H
