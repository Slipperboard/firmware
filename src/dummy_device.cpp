#include "dummy_device.hpp"
#include <cstdio>

DummyDevice dummy_device;

esp_err_t DummyDevice::init()
{
    printf("Dummy device initialized\n");
    return ESP_OK;
}

esp_err_t DummyDevice::deinit()
{
    printf("Dummy device deinitialized\n");
    return ESP_OK;
}
