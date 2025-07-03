#ifdef __cplusplus
extern "C" {
#endif

// Weak stubs for Arduino-style entry points. They allow including
// Arduino.h without requiring setup() and loop() to be implemented.
__attribute__((weak)) void setup() {}
__attribute__((weak)) void loop() {}

#ifdef __cplusplus
}
#endif
