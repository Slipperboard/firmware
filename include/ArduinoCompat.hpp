#ifndef ARDUINO_COMPAT_HPP
#define ARDUINO_COMPAT_HPP

#ifdef ESP_PLATFORM
#include <Arduino.h>
#else
#include <cstdint>

#define INPUT 0x0
#define OUTPUT 0x1
#define HIGH 0x1
#define LOW 0x0

extern "C" {
void setup();
void loop();
void pinMode(uint8_t pin, uint8_t mode);
int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int val);
void dacWrite(uint8_t pin, int val);
void ledcAttachPin(uint8_t pin, uint8_t channel);
void ledcSetup(uint8_t channel, double freq, uint8_t resolution);
void ledcWrite(uint8_t channel, uint32_t duty);
int ledcRead(uint8_t channel);
void delay(std::uint32_t ms);
}
#endif

#endif // ARDUINO_COMPAT_HPP
