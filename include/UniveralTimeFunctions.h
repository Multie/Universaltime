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

#ifndef UniversalTimeFunctions_h
#define UniversalTimeFunctions_h
#include "Arduino.h"
#include "UniversalTime.h"

// Einschaltverzögerung
class TimeFunction {
    public:
        TimeFunction();
        bool SwitchOnDelay(bool value);
        bool SwitchOffDelay(bool value);
        bool MinStateTime(bool value);
        bool Impuls(bool value);
        bool Interval();
        void SetDuration(UniversalTime newDuration);
        UniversalTime GetDuration();
        
    private:
        UniversalTime Duration;
        UniversalTime Endtime;
        bool Started;
        bool Oldstate;
};


#endif