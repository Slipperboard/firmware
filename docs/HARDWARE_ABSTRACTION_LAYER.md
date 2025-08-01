# Hardware Abstraction Layer

`include/Peripheral.hpp` defines a lightweight base class named `Peripheral` that exposes
only a virtual destructor. Generic device categories are provided in separate headers
(`Sensor.hpp`, `Switch.hpp`, `Button.hpp`, and `Display.hpp`) with matching
source files. These classes simply inherit from `Peripheral`. Specific hardware drivers
should derive from one of these classes and perform any required setup in the constructor.

I/O pins are represented by the templated `Pin` class with concrete implementations for
analog (`AnalogPin`), digital (`DigitalPin`) and PWM (`PWMPin`) operation. Each
`Pin` instance can be flagged as *shared* using the optional `isShared`
constructor argument to allow reuse of protocols like I2C and SPI when future
validation prevents duplicate pin assignments.

`Button` now also exposes `press()` and `release()` helpers that measure how long
the button was held. The acceptable duration for a single click can be modified
with `setClickThreshold()`, and calling `release()` returns whether the hold time
was within this limit.

Maintainers: Codex
