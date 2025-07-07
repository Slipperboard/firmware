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

See [docs/HARDWARE_ABSTRACTION_LAYER.md](docs/HARDWARE_ABSTRACTION_LAYER.md) for an overview of the architecture.

### Using Arduino Libraries

If you need to include `Arduino.h` for additional functionality, the build
already provides weak stub implementations of `setup()` and `loop()` in
`src/arduino_stubs.cpp`. This prevents linker errors when the Arduino
framework expects those symbols, while still letting you drive the application
from `app_main()`.

## Building

Build the firmware using the Makefile:

```bash
make build   # builds the firmware via PlatformIO
make clean   # removes PlatformIO artifacts and the test binary
```

Additional tools can check code quality and coverage. Install them with:

```bash
sudo apt-get update
sudo apt-get install -y clang-tidy cppcheck gcovr
```

## Running Unit Tests

Run the Catch2-based test suite with:

```bash
make test
```

which compiles and executes the unit tests with a compact output format.

## Code Quality

Run static analysis with:

```bash
make lint
```
The linter returns a non-zero exit code if any issues are detected. It
searches the `include`, `src`, and `tests` directories so project headers
are recognized by cppcheck.

Generate a coverage report with:

```bash
make coverage
```

