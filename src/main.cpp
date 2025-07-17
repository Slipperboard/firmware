#include <Arduino.h>

// Forward declaration for the actual application entry point
void app_main();

// Provide weak Arduino hooks that simply call into app_main().
void setup() __attribute__((weak));
void loop() __attribute__((weak));

void setup()
{
    app_main();
}

void loop()
{
    // Unused when app_main() contains the main loop
}

void app_main()
{
    Serial.begin(115200);

    while (true)
    {
        Serial.println("Hello, Flipper Zero compatible ESP32!");
        delay(1000);
    }
}
