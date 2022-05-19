
/*
MinStateTime is used to create a output that is minimal x time long and turns of when input is turnd off.

+-------------------------------------------+
|                                           |
|   +---+          +--------------------+   |
+---+   +----------+                    +---+
|Input                                      |
|   |<------>|     |<------>|               |
|   Duration       Duration                 |
|   +--------+     +--------------------+   |
+---+        +-----+                    +---+
|Output                                     |
|                                           |
+-------------------------------------------+
*/

#include "UniveralTimeFunctions.h"
TimeFunction TimeFunc;
TimeFunction InputTimeFunc;
bool input = false;
bool output = false;
double durationSeconds = 5;
void setup()
{
    // Start Serial connection
    Serial.begin(115200);

    // Set Seconds of Time
    UniversalTime durationInput;
    durationInput.setSecond(2);
    InputTimeFunc.SetDuration(durationInput);

    // Set Seconds of Time
    UniversalTime duration;
    duration.setSecond(2);

    // The the time the signal should last
    TimeFunc.SetDuration(duration);

    Serial.println("input:" + String(input) + "\toutput:" + String(output));
    input = true;
}

void loop()
{

    Serial.println("input:" + String(input) + "\toutput:" + String(output) + "\tduration:" + String(durationSeconds));
    if (input)
    {
        durationSeconds = random(1, 5);
        TimeFunc.SetDuration(durationSeconds)
            InputTimeFunc.SwitchOnDelay(false);
    }
    input = InputTimeFunc.SwitchOnDelay(true);
    // To the switch on magic
    output = TimeFunc.SwitchOnDelay(input);

    delay(100);
}