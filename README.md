# Slipperboard

This project is the starting point for building a Flipper Zero–compatible firmware targeting an ESP32-based board. It uses [PlatformIO](https://platformio.org/) for the build environment and the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/) framework.

## Directory Layout

- `src/` – Application source files.
- `include/` – Header files.
- `lib/` – Optional external libraries.
- `platformio.ini` – PlatformIO configuration.

## Entry Point

The firmware starts from an `app_main()` function instead of Arduino's `setup()` and `loop()` routines. The main loop simply prints a message every second using standard ESP-IDF APIs.

### Hardware Abstraction Layer

`include/Peripheral.hpp` defines an abstract base class named `Peripheral` with a single
virtual `init()` method. Generic device classes such as `Module`, `Sensor`,
`Switch`, `Button`, and `Display` simply inherit from this interface. Specific
hardware drivers should derive from one of these classes and implement the
`init()` method to handle device setup.

### Using Arduino Libraries

If you need to include `Arduino.h` for additional functionality, the build
already provides weak stub implementations of `setup()` and `loop()` in
`src/arduino_stubs.cpp`. This prevents linker errors when the Arduino
framework expects those symbols, while still letting you drive the application
from `app_main()`.

## Building

Install PlatformIO and run:

```bash
platformio run
```

This compiles the firmware for the default `esp32dev` environment. A GitHub Actions workflow in `.github/workflows/build.yml` builds the project on pushes, pull requests, and can also be triggered manually from the GitHub UI.
