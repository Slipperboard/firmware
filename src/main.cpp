#include <Arduino.h>

void setup() {
    // initialize serial communication
    Serial.begin(115200);
}

void loop() {
    Serial.println("Hello, Flipper Zero compatible ESP32!");
    delay(1000);
}
