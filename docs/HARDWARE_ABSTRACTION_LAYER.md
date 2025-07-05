# Hardware Abstraction Layer

`include/Peripheral.hpp` defines an abstract base class named `Peripheral` with a single
virtual `init()` method. Generic device categories are provided in separate headers
(`Module.hpp`, `Sensor.hpp`, `Switch.hpp`, `Button.hpp`, and `Display.hpp`) with matching
source files. These classes simply inherit from `Peripheral`. Specific hardware drivers
should derive from one of these classes and implement the `init()` method to handle
device setup.

`Button` now also exposes `press()` and `release()` helpers that measure how long
the button was held. The acceptable duration for a single click can be modified
with `setClickThreshold()`, and calling `release()` returns whether the hold time
was within this limit.
