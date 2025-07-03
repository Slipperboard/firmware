# Slipperboard

This project is the starting point for building a Flipper Zero–compatible firmware targeting an ESP32-based board. It uses [PlatformIO](https://platformio.org/) for the build environment and the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/) framework.

## Directory Layout

- `src/` – Application source files.
- `include/` – Header files.
- `lib/` – Optional external libraries.
- `platformio.ini` – PlatformIO configuration.

## Hardware Abstraction Layer

The `include/hal/hal.hpp` header exposes a light C++ interface for hardware
modules. Devices derive from `hal::Device` and are created by the application
code. They are then passed to `hal::register_device()` which stores pointers in
a small container. Calling `hal::init()` or `hal::deinit()` walks the list and
invokes the corresponding methods on each device, allowing common management of
sensors, buttons and other peripherals.

`src/dummy_device.cpp` shows a minimal example implementation. The main
application instantiates this device and registers it during startup to
illustrate how the HAL is used.

## Entry Point

The firmware starts from an `app_main()` function instead of Arduino's `setup()` and `loop()` routines. The main loop simply prints a message every second using standard ESP-IDF APIs.

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
