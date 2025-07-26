# Slipperboard

<p align="center">
  <img src="assets/repo-logo.png" alt="Slipperboard logo" width="200" />
</p>

This project is a template for building a Flipper Zero–compatible firmware for an ESP32-based board. It uses [PlatformIO](https://platformio.org/) as the build environment with the Arduino framework.

## Development Setup

1. Install the [PlatformIO CLI](https://platformio.org/install).
2. (Optional) Install the Wokwi CLI with `curl -L https://wokwi.com/ci/install.sh | sh` to run the emulator.
3. Clone this repository and run `make build` to compile the firmware.

## Directory Layout

- `src/` – Application source files.
- `include/` – Header files.
- `lib/` – Optional external libraries.
- `platformio.ini` – PlatformIO configuration.

## Entrypoint

The firmware uses the standard Arduino `setup()` and `loop()` routines. The main loop simply prints a message every second using `Serial.println()`.

### Hardware Abstraction Layer

See [docs/HARDWARE_ABSTRACTION_LAYER.md](docs/HARDWARE_ABSTRACTION_LAYER.md) for an overview of the architecture.

### Using Arduino Libraries

Because the firmware targets the Arduino framework, you can include `Arduino.h` and any other Arduino libraries directly in your code.

## Building

Build the firmware using the Makefile:

```bash
make build   # [CI] builds the firmware via PlatformIO and shows size
make clean   # removes PlatformIO artifacts and the test binary
```

Compiler warnings are treated as errors, so address any warnings that appear
during the build.


## Running Unit Tests

Run the Catch2-based test suite with:

```bash
make test # [CI]
```

which compiles and executes the unit tests with a compact output format.

## Code Quality

Run static analysis and coverage tasks:

```bash
make check-format  # [CI]
make lint          # [CI]
make cpplint       # [CI]
make tidy          # [CI]
make coverage      # [CI]
```

Run `make format` to automatically apply clang-format fixes.

This coverage target fails if line coverage is below 100%.

## Precommit

Run the full suite of formatting, linting, documentation, and tests before submitting a change:

```bash
make precommit
```


## Emulator

You can run the firmware inside the [Wokwi](https://wokwi.com/) emulator to test
changes without hardware. First install the Wokwi CLI (for example with
`curl -L https://wokwi.com/ci/install.sh | sh`), build the project, and launch the emulator:

```bash
make build   # [CI]
make emulate
```

The emulator uses `wokwi.toml` and `diagram.json` to locate the firmware files
and board settings. The simulator opens a browser window with the running
firmware.

To verify your emulator configuration without launching the simulator, run:

```bash
make wokwi-sanity # [CI]
```

This checks that `wokwi.toml` and `diagram.json` are well-formed and reference
existing files.

## License

This project is released under the [MIT License](LICENSE).

Maintainers: Codex
