.PHONY: build clean test coverage lint cpplint tidy format check-format precommit emulate wokwi-sanity markdown-lint makefile-lint env docs-check valgrind

# Slipperboard build system
# Convenience targets for building the firmware and running quality checks.

# -----------------------------------------------------------
# Tool command names. Override on the command line if needed
# -----------------------------------------------------------
PIO := platformio
PY  := python3
CXX := g++

# -----------------------------------------------------------
# Names of the unit test executables.
# -----------------------------------------------------------
TEST_BIN := test_all
COV_BIN  := test_all_cov
VALGRIND_BIN := valgrind_app

# -----------------------------------------------------------
# List of tasks executed by `make precommit`
# -----------------------------------------------------------
PRECOMMIT_TARGETS := build makefile-lint markdown-lint check-format cpplint lint tidy docs-check test coverage

# Flags passed to the unit test compiler
TEST_FLAGS = -Ilib/Catch2 -Itests -Iinclude -DCATCH_AMALGAMATED_CUSTOM_MAIN -std=c++17 -Wall -Wextra -Werror
# Sources compiled into the unit tests
TEST_SRCS = \
        lib/Catch2/catch_amalgamated.cpp tests/test_main.cpp \
        tests/MemoryTracker.cpp \
        tests/test_sensor.cpp tests/test_switch.cpp \
                tests/Arduino.cpp \
        tests/test_button.cpp tests/test_display.cpp tests/test_digitalpin.cpp \
        tests/test_analogpin.cpp tests/test_pwmpin.cpp tests/test_tile.cpp \
        tests/test_memory.cpp \
        src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp src/TFTST7735Display.cpp src/Tile.cpp \
        src/Pin.cpp src/DigitalPin.cpp src/AnalogPin.cpp src/PWMPin.cpp

HOST_FLAGS = -Itests -Iinclude -std=c++17 -Wall -Wextra -Werror
VALGRIND_SRCS = tools/valgrind_main.cpp tests/Arduino.cpp \
        src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp src/TFTST7735Display.cpp \
        src/Tile.cpp src/Pin.cpp src/DigitalPin.cpp \
        src/AnalogPin.cpp src/PWMPin.cpp

# File lists for code formatting and analysis tools
FMT_FILES := $(shell git ls-files 'src/*.cpp' 'include/*.hpp' 'tests/*.cpp' 'tests/*.hpp')
CPPLINT_FILES := $(FMT_FILES)
TIDY_FILES := $(shell git ls-files 'src/*.cpp' | grep -v 'src/main.cpp')


## Build the firmware and show size information
build:
	$(PIO) run
	$(PIO) run --target size

## Remove build artifacts and coverage data
clean:
	$(PIO) run -t clean
	$(RM) $(TEST_BIN) $(COV_BIN)
	$(RM) *.gcno *.gcda

## Apply clang-format fixes in place
format:
	clang-format -i $(FMT_FILES)

## Check code formatting without modifying files
check-format:
	clang-format --dry-run --Werror $(FMT_FILES)

## Run Google's cpplint style checker
cpplint:
	cpplint $(CPPLINT_FILES) || (echo "cpplint style violations found" && exit 1)

## Static analysis via cppcheck
## --force checks all preprocessor paths
## --max-configs suppresses "too many #ifdef" warnings
lint:
	cppcheck --enable=all --inconclusive --std=c++17 --force --max-configs=2 --inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude --suppress=unmatchedSuppression --suppress=unusedFunction \
	--error-exitcode=1 -Iinclude -Isrc \
	src include

## Clang-Tidy analysis
tidy:
	clang-tidy $(TIDY_FILES) -- -std=c++17 -Iinclude -Itests > clang-tidy.log 2>&1
		cat clang-tidy.log
		! grep -E "(warning:|error:)" clang-tidy.log
		rm clang-tidy.log

## Verify Doxygen documentation builds cleanly
docs-check:
	doxygen Doxyfile

## Lint Markdown documentation
markdown-lint:
	$(PY) scripts/markdown_lint.py $(FILES)

## Ensure Makefile style rules are followed
makefile-lint:
	$(PY) scripts/makefile_lint.py Makefile

## Compile and run Catch2 unit tests
test:
	$(CXX) $(TEST_FLAGS) $(TEST_SRCS) -o $(TEST_BIN)
	./$(TEST_BIN) --reporter console --success

## Run tests with coverage and enforce 100% line coverage
coverage:
	$(CXX) $(TEST_FLAGS) --coverage $(TEST_SRCS) -o $(COV_BIN)
	./$(COV_BIN) --reporter console --success
	gcovr -r . --exclude-directories=lib --exclude='.*Catch2.*' --print-summary --fail-under-line=100
	$(RM) *.gcno *.gcda $(COV_BIN)

## Build and run the host example under Valgrind
valgrind: $(VALGRIND_BIN)
	valgrind --leak-check=full ./$(VALGRIND_BIN)

$(VALGRIND_BIN): $(VALGRIND_SRCS)
	$(CXX) $(HOST_FLAGS) $(VALGRIND_SRCS) -o $(VALGRIND_BIN)


## Run all checks required before committing changes
precommit: $(PRECOMMIT_TARGETS)

## Launch the firmware in the Wokwi emulator
emulate: build
	wokwi-cli sim

## Validate Wokwi configuration files
wokwi-sanity:
	$(PY) scripts/wokwi_sanity.py

## Install toolchain and Git hooks
env:
	./scripts/setup_env.sh
	./scripts/install_hooks.sh

