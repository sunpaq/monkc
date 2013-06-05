#include "monkc.h"
#include "MCUnitTest.h"
#include "MCClock.h"

#ifndef TestMCClock_
#define TestMCClock_

class(TestMCClock);
	MCClock* toBeTest;
end(TestMCClock);

method(TestMCClock, setTimeToNow, xxx);
method(TestMCClock, setTime, xxx);
method(TestMCClock, adjustTime, xxx);
method(TestMCClock, setRawtime, xxx);
method(TestMCClock, setRawtimeFields, xxx);

method(TestMCClock, getTime, xxx);
method(TestMCClock, getRawtime, xxx);
method(TestMCClock, getTimeByString, xxx);
method(TestMCClock, getCPUClocksPerSecond, xxx);
method(TestMCClock, getCPUClocksSinceStart, xxx);
method(TestMCClock, getCurrentTimeString, xxx);
method(TestMCClock, getCurrentGMTTimeString, xxx);

method(TestMCClock, printTime, xxx);
method(TestMCClock, printCurrentTime, xxx);
method(TestMCClock, printCurrentGMTTime, xxx);

//override
method(TestMCClock, setUp, xxx);
method(TestMCClock, tearDown, xxx);
#endif

/*
method(MCClock, setTimeToNow, xxx);
method(MCClock, setTime, int tm_sec, int tm_min, int tm_hour, 
						 int tm_mday, int tm_mon, int tm_year,
						 int tm_wday);
method(MCClock, adjustTime, int tm_sec, int tm_min, int tm_hour, 
                            int tm_mday, int tm_mon, int tm_year,
                            int tm_wday);

method(MCClock, setRawtime, struct tm rawtime_in);
method(MCClock, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
							      int tm_mday, int tm_mon, int tm_year,
							      int tm_wday, int tm_yday, int tm_isdst);

method(MCClock, getTime, time_t* const result);
method(MCClock, getRawtime, struct tm* const result);
method(MCClock, getTimeByString, xxx) 								returns(char*);
method(MCClock, getCPUClocksPerSecond, clock_t* const result);
method(MCClock, getCPUClocksSinceStart, clock_t* const result);
method(MCClock, getCurrentTimeString, xxx) 							returns(char*);//retrun the same format as asctime: Sun Sep 16 01:03:52 1973\n\0
method(MCClock, getCurrentGMTTimeString, xxx) 						returns(char*);

method(MCClock, printTime, xxx);
method(MCClock, printCurrentTime, xxx);
method(MCClock, printCurrentGMTTime, xxx);
*/