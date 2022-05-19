
/*
TOm (TON) is used to in SPS to delay the output and if input is false while the delay is runnig no output is emitted.
+--------------------------------------+
|                                      |
|     +---------------------------+    |
+-----+                           +----+
|Input                                 |
|     |<----------->|                  |
|       Duration                       |
|                   +------------+     |
+-------------------+            +-----+
|Output                                |
+--------------------------------------+
*/

#include "UniveralTimeFunctions.h"
TimeFunction TimeFunc;
bool input = false;
bool output = false;
void setup()
{
    // Start Serial connection
    Serial.begin(115200);

    // Set Seconds of Time
    UniversalTime duration;
    duration.setSecond(30);

    // Set Duration of TOff
    TimeFunc.SetDuration(duration);

    Serial.println("Set Timer for 30 Seconds");
    Serial.println("input:" + String(input) + "\toutput:" + String(output));
    input = true;
}

void loop()
{

    Serial.println("input:" + String(input) + "\toutput:" + String(output));

    // To the switch on magic
    output = TimeFunc.SwitchOnDelay(input);
    delay(100);
    if (input)
    {
        input = false;
    }
}