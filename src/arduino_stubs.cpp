#include "ArduinoCompat.hpp"
#ifndef ESP_PLATFORM
#include <cstdint>
// GCOVR_EXCL_START

static bool digital_state[256];
static int analog_state[256];
static std::uint32_t pwm_state[16];

extern "C" {
void pinMode(uint8_t, uint8_t) {}
int digitalRead(uint8_t pin) { return digital_state[pin] ? 1 : 0; }
void digitalWrite(uint8_t pin, uint8_t val) { digital_state[pin] = val != 0; }
int analogRead(uint8_t pin) { return analog_state[pin]; }
void analogWrite(uint8_t pin, int val) { analog_state[pin] = val; }
void dacWrite(uint8_t pin, int val) { analog_state[pin] = val; }
void ledcAttachPin(uint8_t, uint8_t) {}
void ledcSetup(uint8_t, double, uint8_t) {}
void ledcWrite(uint8_t channel, uint32_t duty) { pwm_state[channel] = duty; }
int ledcRead(uint8_t channel) { return static_cast<int>(pwm_state[channel]); }
void delay(std::uint32_t) {}
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
__attribute__((weak)) void setup() {}
__attribute__((weak)) void loop() {}
#ifdef __cplusplus
}
#endif

#ifndef ESP_PLATFORM
// GCOVR_EXCL_STOP
#endif
