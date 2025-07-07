.PHONY: build test clean lint coverage format

TEST_FLAGS = -Ilib/Catch2 -Itests -Iinclude -DCATCH_AMALGAMATED_CUSTOM_MAIN -std=c++17
TEST_SRCS = \
        lib/Catch2/catch_amalgamated.cpp tests/test_main.cpp \
        tests/MemoryTracker.cpp \
	tests/test_module.cpp tests/test_sensor.cpp tests/test_switch.cpp \
	tests/test_button.cpp tests/test_display.cpp tests/test_digitalpin.cpp \
	tests/test_analogpin.cpp tests/test_oleddisplay.cpp \
	src/Module.cpp src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp \
	src/OledDisplay.cpp \
        src/Pin.cpp src/DigitalPin.cpp src/AnalogPin.cpp

FMT_FILES := $(shell git ls-files 'src/*.cpp' 'include/*.hpp' 'tests/*.cpp' 'tests/*.hpp')

build:
	platformio run

test:
	g++ $(TEST_FLAGS) $(TEST_SRCS) -o test_all
	./test_all --reporter compact

lint:
	cppcheck --enable=all --inconclusive --std=c++17 --force --max-configs=1 --inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude --suppress=unmatchedSuppression --suppress=unusedFunction \
	--error-exitcode=1 -Iinclude -Isrc \
	src include
	
coverage:
	g++ $(TEST_FLAGS) --coverage $(TEST_SRCS) -o test_all_cov
	./test_all_cov --reporter compact
	gcovr -r . --exclude-directories=lib --exclude='.*Catch2.*' --print-summary
	$(RM) *.gcno *.gcda test_all_cov

format:
	clang-format -i $(FMT_FILES)

clean:
	platformio run -t clean
	$(RM) test_all test_all_cov
	$(RM) *.gcno *.gcda
