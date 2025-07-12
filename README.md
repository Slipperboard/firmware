# Slipperboard

<p align="center">
  <img src="assets/repo-logo.png" alt="Slipperboard logo" width="200" />
</p>

This project is the starting point for building a Flipper Zero–compatible firmware targeting an ESP32-based board. It uses [PlatformIO](https://platformio.org/) for the build environment and the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/) framework.

## Directory Layout

- `src/` – Application source files.
- `include/` – Header files.
- `lib/` – Optional external libraries.
- `platformio.ini` – PlatformIO configuration.

## Entrypoint

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
make build   # builds the firmware via PlatformIO and shows size
make clean   # removes PlatformIO artifacts and the test binary
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

Check code conventions with cpplint:

```bash
make cpplint
```

For additional diagnostics, run clang-tidy over the source files with:

```bash
make tidy
```

Generate a coverage report:

```bash
make coverage
```
This target fails if line coverage is below 100%.

## Formatting

Automatically apply the project's clang-format style with:

```bash
make format
```

Check formatting without modifying files:

```bash
make check-format
```

## Precommit

Run all checks sequentially before committing:

```bash
make precommit
```

This command runs `make build`, `make check-format`, `make cpplint`,
`make lint`, `make tidy`, `make test` and `make coverage` in order.

## Nix Development Shell

You can create a reproducible environment using [Nix](https://nixos.org/). After installing Nix, run:

```bash
nix develop
```

This drops you into a shell with PlatformIO, gcc and the Makefile tools available.

## Dev Container

To work inside a fully configured VS Code dev container, run:

```bash
make devcontainer
```

This command starts the container defined in `.devcontainer` and attaches to it.

## Emulator

You can also run the firmware inside the [Wokwi](https://wokwi.com/) emulator to
test changes without hardware. First install the Wokwi CLI (e.g.
`npm install -g @wokwi/cli`) and build the project:

```bash
make build
```

Then start the simulator:

```bash
make emulate
```

The emulator uses `wokwi.toml` and `diagram.json` to locate the firmware files
and board settings. The simulator opens a browser window with the running
firmware.

To verify your emulator configuration without launching the simulator, run:

```bash
make wokwi-sanity
```

This checks that `wokwi.toml` and `diagram.json` are well-formed and reference
existing files.
