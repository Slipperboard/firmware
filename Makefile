.PHONY: build test clean

build:
	platformio run

test:
	g++ -Ilib/Catch2 -Itests -Iinclude -DCATCH_AMALGAMATED_CUSTOM_MAIN -std=c++17 \
		lib/Catch2/catch_amalgamated.cpp tests/test_main.cpp \
		tests/MemoryTracker.cpp \
		tests/test_module.cpp tests/test_sensor.cpp tests/test_switch.cpp \
		tests/test_button.cpp tests/test_display.cpp tests/test_digitalpin.cpp \
		tests/test_analogpin.cpp tests/test_oled096display.cpp \
		src/Module.cpp src/Sensor.cpp src/Switch.cpp src/Button.cpp src/Display.cpp \
                src/Oled096Display.cpp \
                src/Adafruit_SSD1306.cpp src/lvgl.cpp \
                src/Pin.cpp src/DigitalPin.cpp src/AnalogPin.cpp \
                -o test_all
	./test_all --reporter compact

clean:
	platformio run -t clean
	$(RM) test_all
