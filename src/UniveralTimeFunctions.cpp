/*
 *   Copyright (c) 2022 Malte Hering
 *   All rights reserved.

 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at

 *   http://www.apache.org/licenses/LICENSE-2.0

 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "Arduino.h"
#include "UniveralTimeFunctions.h"

TimeFunction::TimeFunction()
{
    Duration = UniversalTime();
    Endtime = UniversalTime();
    Started = false;
    Oldstate = false;
}

bool TimeFunction::SwitchOnDelay(bool value)
{

    // LogDebug2("ton",String(value) + "\t" + String(Oldstate));
    bool output = false;
    if (value && !Oldstate)
    {
        // Start
        Started = true;
        Endtime = UniversalTime::Now().add(Duration);
    }
    else if (value && Oldstate && Started)
    {
        // Running
        output = (Endtime.compare(UniversalTime::Now()) >= 0);
    }
    else if (!value && Oldstate)
    {
        // Abort
        Started = false;
    }
    else
    {
    }
    /*else if (!value && !Oldstate) {
        // Idle
    }*/
    // Serial.println( "In:" + String(value) + " Old:" + String(Oldstate) +  " Out:" + String(output) + " Started:" + String(Started) + " Cur:" + UniversalTime::Now().toISO8601() +  " End:" + Endtime.toISO8601());
    Oldstate = value;
    return output;
};
bool TimeFunction::SwitchOffDelay(bool value)
{
    bool output = true;
    if (!value && Oldstate)
    {
        // Start
        Started = true;
        Endtime = UniversalTime::Now().add(Duration);
    }
    else if (!value && !Oldstate && Started)
    {
        // Running
        output = !(Endtime.compare(UniversalTime::Now()) >= 0);
    }
    else if (value && !Oldstate)
    {
        // Abort
        Started = false;
    }
    // else if (value && Oldstate )
    //{
    //  Idle

    //}
    // Serial.println( "In:" + String(value) + " Old:" + String(Oldstate) +  " Out:" + String(output) + " Started:" + String(Started) + " Cur:" + UniversalTime::Now().toISO8601() +  " End:" + Endtime.toISO8601());
    Oldstate = value;
    return output;
};
bool TimeFunction::Impuls(bool value)
{
    bool output = false;
    if (value && !Started)
    {
        // Start
        Started = true;
        Endtime = UniversalTime::Now().add(Duration);
        output = true;
    }
    else if (Started)
    {
        // Running
        output = (Endtime.compare(UniversalTime::Now()) <= 0);
        if (!output)
        {
            Started = false;
        }
    }
    // else if (!value && Oldstate )
    //{
    //  Abort
    //    Started = false;
    //}
    // else if (value && Oldstate )
    //{
    // Idle
    //}
    // Serial.println( "In:" + String(value) + " Old:" + String(Oldstate) +  " Out:" + String(output) + " Started:" + String(Started) + " Cur:" + UniversalTime::Now().toISO8601() +  " End:" + Endtime.toISO8601());
    Oldstate = value;
    return output;
}

bool TimeFunction::Interval()
{
    bool output = false;
    if (!Started)
    {
        Endtime = UniversalTime::Now().add(Duration);
        Started = true;
    }
    else if (Endtime.compare(UniversalTime::Now()) >= 0)
    {
        // Elapsed
        Endtime = UniversalTime::Now().add(Duration);
        output = true;
    }

    // Serial.println( " Old:" + String(Oldstate) +  " Out:" + String(output) + " Started:" + String(Started) + " Cur:" + UniversalTime::Now().toISO8601() +  " End:" + Endtime.toISO8601());
    return output;
};

bool TimeFunction::MinStateTime(bool value)
{
    if (value != Oldstate)
    {
        // Start Changing
        if (Endtime.compare(UniversalTime::Now()) >= 0)
        {
            Endtime = UniversalTime::Now().add(Duration);
            Oldstate = value;
            
        }
    }

    // Serial.print("OldState:"  + String(Oldstate) + "\t");

    return Oldstate;
};

void TimeFunction::SetDuration(UniversalTime newDuration) {
    Endtime.subtractTime(Duration);
    Endtime.addTime(newDuration);
    Duration = newDuration;
};

UniversalTime TimeFunction::GetDuration() {
    return Duration;
};