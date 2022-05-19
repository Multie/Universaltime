
/*
Interval is uesd to create a Puls every x [sec,min,hour...]
+--------------------------------+
|                                |
|     |<------->|<------->|      |
|      Duration  Duration        |
|                                |
|     |         |         |      |                        +
+-----+---------+---------+------+
|Output                          |
+--------------------------------+
*/

#include "UniveralTimeFunctions.h"
TimeFunction TimeFunc;
void setup()
{
    // Start Serial connection
    Serial.begin(115200);

    // Set Seconds of Time
    UniversalTime duration;
    duration.setSecond(1);

    // Set Duration of TOff
    TimeFunc.SetDuration(duration);

    Serial.println("Set Interval of 1 Seconds");
}

void loop()
{
    // To the impuls magic
    if (TimeFunc.Interval()) {
        Serial.println("tick");
    }
    delay(100);
}