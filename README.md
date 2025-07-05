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
virtual `init()` method. Generic device categories are provided in separate headers
(`Module.hpp`, `Sensor.hpp`, `Switch.hpp`, `Button.hpp`, and `Display.hpp`) with matching
source files. These classes simply inherit from `Peripheral`. Specific hardware drivers
should derive from one of these classes and implement the `init()` method to handle
device setup.

`Button` now also exposes `press()` and `release()` helpers that measure how long
the button was held. The acceptable duration for a single click can be modified
with `setClickThreshold()`, and calling `release()` returns whether the hold time
was within this limit.

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

You can also use the provided Makefile as a convenience:

```bash
make build   # builds the firmware via PlatformIO
make clean   # removes PlatformIO artifacts and the test binary
```

## Running Unit Tests

You can compile the Catch2-based test suite with a single `g++` command:

```bash
g++ -Ilib/Catch2 -Itests -Iinclude -DCATCH_AMALGAMATED_CUSTOM_MAIN -std=c++17 \
    lib/Catch2/catch_amalgamated.cpp tests/test_main.cpp \
    tests/MemoryTracker.cpp \
    tests/test_module.cpp tests/test_sensor.cpp tests/test_switch.cpp \
    tests/test_button.cpp tests/test_display.cpp tests/test_digitalpin.cpp \
    tests/test_analogpin.cpp \
    src/Module.cpp src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp \
    src/Pin.cpp src/DigitalPin.cpp src/AnalogPin.cpp \
    -o test_all
./test_all -s
```

This reflects the new split test layout. Each device type has its own test file, and `test_main.cpp` defines a shared test runner and allocation counter.

For convenience you can simply run:

```bash
make test
```

which compiles and executes the unit tests with a compact output format.
