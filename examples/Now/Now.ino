

#include "UniversalTime.h"

UniversalTime time1;

void setup() {
    // Start Serial connection
    Serial.begin(115200);

    // Set Seconds of Time
    time1.setSecond(30);
    Serial.println("Set Timer for 30 Seconds")
}

void loop() {
    // Compare Time 1 with current Time
    if (time1.compare(UniveralTime::Now()) == -1) {
        Serial.println("After 30 Seconds");
    }
    else {
        Serial.println("Before 30 Seconds")
    }
    delay(100);
}