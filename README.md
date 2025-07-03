# Slipperboard

This project is the starting point for building a Flipper Zero–compatible firmware targeting an ESP32-based board. It uses [PlatformIO](https://platformio.org/) for the build environment and the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/) framework.

## Directory Layout

- `src/` – Application source files.
- `include/` – Header files.
- `lib/` – Optional external libraries.
- `platformio.ini` – PlatformIO configuration.

## Entry Point

The firmware starts from an `app_main()` function instead of Arduino's `setup()` and `loop()` routines. The main loop simply prints a message every second using standard ESP-IDF APIs.

## Building

Install PlatformIO and run:

```bash
platformio run
```

This compiles the firmware for the default `esp32dev` environment. A GitHub Actions workflow in `.github/workflows/build.yml` automatically builds the project on every push.
