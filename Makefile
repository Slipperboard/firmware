.PHONY: build release size test clean lint coverage

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

build:
	platformio run

release:
	platformio run --project-conf platformio-release.ini

size:
	platformio run --target size

test:
	g++ $(TEST_FLAGS) $(TEST_SRCS) -o test_all
	./test_all --reporter compact

lint:
	cppcheck --enable=all --inconclusive --std=c++17 --force src include tests

coverage:
	g++ $(TEST_FLAGS) --coverage $(TEST_SRCS) -o test_all_cov
	./test_all_cov --reporter compact
	gcovr -r . --exclude-directories=lib --exclude='.*Catch2.*' --print-summary
	$(RM) *.gcno *.gcda test_all_cov

clean:
	platformio run -t clean
	$(RM) test_all test_all_cov
	$(RM) *.gcno *.gcda
