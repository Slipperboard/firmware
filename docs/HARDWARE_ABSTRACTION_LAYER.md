# Hardware Abstraction Layer

`include/Peripheral.hpp` defines a minimal base class named `Peripheral`.
Generic device categories are provided in separate headers (`Module.hpp`, `Sensor.hpp`,
`Switch.hpp`, `Button.hpp`, and `Display.hpp`) with matching source files. Specific
hardware drivers should derive from one of these classes and perform any device setup
inside their constructors.

`Button` now also exposes `press()` and `release()` helpers that measure how long
the button was held. The acceptable duration for a single click can be modified
with `setClickThreshold()`, and calling `release()` returns whether the hold time
was within this limit.
