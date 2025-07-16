#ifndef ARDUINO_H
#define ARDUINO_H

#include <cstdint>

#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

extern int pinModes[64];
extern int digitalPinStates[64];
extern int analogPinStates[64];

inline void pinMode(int pin, int mode) { pinModes[pin] = mode; }
inline int digitalRead(int pin) { return digitalPinStates[pin]; }
inline void digitalWrite(int pin, int val) { digitalPinStates[pin] = val; }
inline int analogRead(int pin) { return analogPinStates[pin]; }
inline void analogWrite(int pin, int val) { analogPinStates[pin] = val; }
inline void delay(unsigned long) {}

class HardwareSerial {
public:
    inline void begin(unsigned long) {}
    inline void println(const char*) {}
};

extern HardwareSerial Serial;

#endif // ARDUINO_H
