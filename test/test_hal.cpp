#include <unity.h>
#include "hal/hal.hpp"

using hal::Device;

class MockDevice : public Device {
public:
    bool initialized = false;
    bool deinitialized = false;

    esp_err_t init() override {
        initialized = true;
        return ESP_OK;
    }
    esp_err_t deinit() override {
        deinitialized = true;
        return ESP_OK;
    }
};

void setUp(void) {
    hal::reset();
}

void tearDown(void) {
    hal::reset();
}

void test_register_device_limit() {
    MockDevice devices[hal::MAX_DEVICES];
    for (std::size_t i = 0; i < hal::MAX_DEVICES; ++i) {
        TEST_ASSERT_EQUAL_INT(ESP_OK, hal::register_device(&devices[i]));
    }
    MockDevice extra;
    TEST_ASSERT_EQUAL_INT(ESP_ERR_NO_MEM, hal::register_device(&extra));
}

void test_init_and_deinit() {
    MockDevice dev;
    hal::register_device(&dev);
    TEST_ASSERT_FALSE(dev.initialized);
    hal::init();
    TEST_ASSERT_TRUE(dev.initialized);
    TEST_ASSERT_FALSE(dev.deinitialized);
    hal::deinit();
    TEST_ASSERT_TRUE(dev.deinitialized);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_register_device_limit);
    RUN_TEST(test_init_and_deinit);
    return UNITY_END();
}
