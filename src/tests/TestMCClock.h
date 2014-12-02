#include "monkc.h"
#include "MCUnitTest.h"
#include "MCClock.h"

#ifndef TestMCClock_
#define TestMCClock_

monkc(TestMCClock);
	MCClock* toBeTest;
end(TestMCClock);

method(TestMCClock, void, setTimeToNow, xxx);
method(TestMCClock, void, setTime, xxx);
method(TestMCClock, void, adjustTime, xxx);
method(TestMCClock, void, setRawtime, xxx);
method(TestMCClock, void, setRawtimeFields, xxx);

method(TestMCClock, void, getTime, xxx);
method(TestMCClock, void, getRawtime, xxx);
method(TestMCClock, void, getTimeByString, xxx);
method(TestMCClock, void, getCPUClocksPerSecond, xxx);
method(TestMCClock, void, getCPUClocksSinceStart, xxx);
method(TestMCClock, void, getCurrentTimeString, xxx);
method(TestMCClock, void, getCurrentGMTTimeString, xxx);

method(TestMCClock, void, printTime, xxx);
method(TestMCClock, void, printCurrentTime, xxx);
method(TestMCClock, void, printCurrentGMTTime, xxx);

//override
method(TestMCClock, void, setUp, xxx);
method(TestMCClock, void, tearDown, xxx);
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