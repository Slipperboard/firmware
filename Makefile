.PHONY: build clean test coverage lint cpplint tidy format check-format precommit emulate wokwi-sanity

TEST_FLAGS = -Ilib/Catch2 -Itests -Iinclude -DCATCH_AMALGAMATED_CUSTOM_MAIN -std=c++17 -Wall -Wextra -Werror
TEST_SRCS = \
	lib/Catch2/catch_amalgamated.cpp tests/test_main.cpp \
	tests/MemoryTracker.cpp \
	tests/test_module.cpp tests/test_sensor.cpp tests/test_switch.cpp \
        tests/test_button.cpp tests/test_display.cpp tests/test_digitalpin.cpp \
        tests/test_analogpin.cpp tests/test_pwmpin.cpp tests/test_oleddisplay.cpp \
        tests/test_memory.cpp \
        src/Module.cpp src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp \
        src/OledDisplay.cpp \
        src/Pin.cpp src/DigitalPin.cpp src/AnalogPin.cpp src/PWMPin.cpp

FMT_FILES := $(shell git ls-files 'src/*.cpp' 'include/*.hpp' 'tests/*.cpp' 'tests/*.hpp')
CPPLINT_FILES := $(FMT_FILES)
TIDY_FILES := $(shell git ls-files 'src/*.cpp' | grep -v 'src/main.cpp')

build:
	platformio run
	platformio run --target size

clean:
	platformio run -t clean
	$(RM) test_all test_all_cov
	$(RM) *.gcno *.gcda

format:
	clang-format -i $(FMT_FILES)

check-format:
	clang-format --dry-run --Werror $(FMT_FILES)

cpplint:
	cpplint $(CPPLINT_FILES) || (echo "cpplint style violations found" && exit 1)

# Use --force to check all preprocessor configurations.
# --max-configs suppresses cppcheck's "too many #ifdef" warnings.
lint:
	cppcheck --enable=all --inconclusive --std=c++17 --force --max-configs=2 --inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude --suppress=unmatchedSuppression --suppress=unusedFunction \
	--error-exitcode=1 -Iinclude -Isrc \
	src include

tidy:
	clang-tidy $(TIDY_FILES) -- -std=c++17 -Iinclude > clang-tidy.log 2>&1
	cat clang-tidy.log
	! grep -E "(warning:|error:)" clang-tidy.log
	rm clang-tidy.log

test:
	g++ $(TEST_FLAGS) $(TEST_SRCS) -o test_all
	./test_all --reporter console --success

coverage:
	g++ $(TEST_FLAGS) --coverage $(TEST_SRCS) -o test_all_cov
	./test_all_cov --reporter console --success
	gcovr -r . --exclude-directories=lib --exclude='.*Catch2.*' --print-summary --fail-under-line=100
	$(RM) *.gcno *.gcda test_all_cov

precommit:
	$(MAKE) build
	$(MAKE) check-format
	$(MAKE) cpplint
	$(MAKE) lint
	$(MAKE) tidy
	$(MAKE) test
	$(MAKE) coverage

emulate: build
	wokwi-cli .

wokwi-sanity:
	python3 scripts/wokwi_sanity.py
