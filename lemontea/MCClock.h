#include <time.h>
#include "MCContext.h"

#ifndef MCClock_
#define MCClock_

class(MCClock, MCObject,
      struct tm rawtime;
      char* currentTimeBuff;
      char* currentGMTBuff;
);

method(MCClock, void, bye, voida);
method(MCClock, MCClock*, setTimeToNow, voida);
method(MCClock, void, setTime, int tm_sec, int tm_min, int tm_hour, 
						 int tm_mday, int tm_mon, int tm_year,
						 int tm_wday);
method(MCClock, void, adjustTime, int tm_sec, int tm_min, int tm_hour, 
                            int tm_mday, int tm_mon, int tm_year,
                            int tm_wday);

method(MCClock, void, setRawtime, struct tm rawtime_in);
method(MCClock, void, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
							      int tm_mday, int tm_mon, int tm_year,
							      int tm_wday, int tm_yday, int tm_isdst);

method(MCClock, void, getTime, time_t* const result);
method(MCClock, void, getRawtime, struct tm* const result);
method(MCClock, char*, getTimeByString, voida);
method(MCClock, void, getCPUClocksPerSecond, clock_t* const result);
method(MCClock, void, getCPUClocksSinceStart, clock_t* const result);
method(MCClock, char*, getCurrentTimeString, voida);//retrun the same format as asctime: Sun Sep 16 01:03:52 1973\n\0
method(MCClock, char*, getCurrentGMTTimeString, voida);

method(MCClock, void, printTime, voida);
method(MCClock, void, printCurrentTime, voida);
method(MCClock, void, printCurrentGMTTime, voida);

char* MCClock_rawtime2String(time_t* timeval);
char* MCClock_settableTime2String(struct tm *tm);
struct tm* MCClock_rawtime2SettableTimeGMT(time_t* timeval);
struct tm* MCClock_rawtime2SettableTimeLocal(time_t* timeval);

#define no_change 60000
enum weekday {
	SUN, //SUNDAY,
	MON, //MONDAY,
	TUE, //TUESDAY,
	WED, //WEDNESDAY,
	THU, //THURSDAY,
	FRI, //FRIDAY,
	SAT, //SATURDAY,
};

enum month {
	JAN, //JANUARY,
	FEB, //FEBRUARY,
	MAR, //MARCH,
	APR, //APRIL,
	MAY,
	JUN, //JUNE,
	JUL, //JULY,
	AUG, //AUGUST,
	SEP, //SEPTEMBER,
	OCT, //OCTOBER,
	NOV, //NOVEMBER,
	DEC, //DECEMBER,
};

#endif

/*
clock();----------CPU clock, use with CLOCKS_PER_SEC

time();-----------(value to value)current calendar time to time_t value
asctime();--------(struct to string)time to ASCII code, return the string
localtime();------(value to struct)convert struct time_t to local tm struct
ctime();----------(value to string)local time to char, return the string, equal to asctime(localtime())

difftime();-------(value to double)difference of seconds
gmtime();---------(value to struct)UTC/GMT time, return tm struct
mktime();---------(struct to value)make time_t use tm struct
strftime();-------(struct to string)string format time, make a string as format use tm struct

size_t
clock_t

time_t------------long

struct tm
    int tm_sec;    // seconds after the minute (0 to 61)
    int tm_min;    // minutes after the hour (0 to 59)
    int tm_hour;   // hours since midnight (0 to 23)
    int tm_mday;   // day of the month (1 to 31)
    int tm_mon;    // months since January (0 to 11)
    int tm_year;   // years since 1900
    int tm_wday;   // days since Sunday (0 to 6 Sunday=0)
    int tm_yday;   // days since January 1 (0 to 365)
    int tm_isdst;  // Daylight Savings Time

//1. rawTime: time_t
//2. settableTime: tm
//3. stringTime: char*
*/
