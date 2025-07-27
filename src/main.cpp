/**
 * @file main.cpp
 * @brief Entry point for the example firmware.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include <Arduino.h>

// Forward declaration for the actual application entry point
void app_main();

void runApp();

// Provide weak Arduino hooks that simply call into app_main().
void setup() __attribute__((weak));
void loop() __attribute__((weak));

/** Arduino setup function that delegates to app_main(). */
void setup()
{
    app_main();
}

/** Empty Arduino loop used when app_main() runs its own loop. */
void loop()
{
    // Unused when app_main() contains the main loop
}

/**
 * @brief Application entry point.
 *
 * This function is executed from setup() and contains the main firmware loop.
 */
void app_main()
{
    Serial.begin(115200);

    runApp();

    while (true)
    {
        Serial.println("Hello, Flipper Zero compatible ESP32!");
        delay(1000);
    }
}

void runApp()
{
}
