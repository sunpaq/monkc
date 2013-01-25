#include "MCClock.h"

method(MCClock, setTimeToNow, xxx)
{
	time_t timer = time(NULL);
	this->rawtime = *localtime(&timer);
}

method(MCClock, setTime, int tm_sec, int tm_min, int tm_hour, 
						 int tm_mday, int tm_mon, int tm_year,
						 int tm_wday)
{
	if(tm_sec!=no_change) this->rawtime.tm_sec = tm_sec;
	if(tm_min!=no_change) this->rawtime.tm_min = tm_min;
	if(tm_hour!=no_change) this->rawtime.tm_hour = tm_hour;
	if(tm_mday!=no_change) this->rawtime.tm_mday = tm_mday;
	if(tm_mon!=no_change) this->rawtime.tm_mon = tm_mon;
	int year = tm_year-1900;
	if(tm_year!=no_change) this->rawtime.tm_year = year;
	if(tm_wday!=no_change) this->rawtime.tm_wday = tm_wday;
}

method(MCClock, adjustTime, int tm_sec, int tm_min, int tm_hour, 
                            int tm_mday, int tm_mon, int tm_year,
                            int tm_wday)
{
	if(tm_sec!=no_change) this->rawtime.tm_sec += tm_sec;
	if(tm_min!=no_change) this->rawtime.tm_min += tm_min;
	if(tm_hour!=no_change) this->rawtime.tm_hour += tm_hour;
	if(tm_mday!=no_change) this->rawtime.tm_mday += tm_mday;
	if(tm_mon!=no_change) this->rawtime.tm_mon += tm_mon;
	if(tm_year!=no_change) this->rawtime.tm_year += tm_year;
	if(tm_wday!=no_change) this->rawtime.tm_wday += tm_wday;
}

method(MCClock, setRawtime, struct tm rawtime_in)
{
	this->rawtime = rawtime_in;
}

method(MCClock, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
							      int tm_mday, int tm_mon, int tm_year,
							      int tm_wday, int tm_yday, int tm_isdst)
{
	if(tm_sec!=no_change)this->rawtime.tm_sec = tm_sec;
	if(tm_sec!=no_change)this->rawtime.tm_min = tm_min;
	if(tm_sec!=no_change)this->rawtime.tm_hour = tm_hour;
	//
	if(tm_sec!=no_change)this->rawtime.tm_mday = tm_mday;
	if(tm_sec!=no_change)this->rawtime.tm_mon = tm_mon;
	if(tm_sec!=no_change)this->rawtime.tm_year = tm_year-1900;
	//
	if(tm_sec!=no_change)this->rawtime.tm_wday = tm_wday;
	if(tm_sec!=no_change)this->rawtime.tm_yday = tm_yday;
	if(tm_sec!=no_change)this->rawtime.tm_isdst = tm_isdst;
}

method(MCClock, getTime, time_t* const result)
{
	*result = mktime(&(this->rawtime));
}

method(MCClock, getRawtime, struct tm* const result)
{
	*result = this->rawtime;
}

static char* strbuff[50];
method(MCClock, getTimeByString, xxx)
{
	strcpy(strbuff, asctime(&(this->rawtime)));
	return strbuff;
}

method(MCClock, getCPUClocksPerSecond, clock_t* const result)
{
	*result = CLOCKS_PER_SEC;
}

method(MCClock, getCPUClocksSinceStart, clock_t* const result)
{
	*result = clock();
}

static char* buff[50];
method(MCClock, getCurrentTimeString, xxx)
{
	time_t timer = time(NULL);
	strcpy(buff, asctime(localtime(&timer)));
	//return asctime(localtime(&timer)));
	return buff;
}

static char* gmbuff[50];
method(MCClock, getCurrentGMTTimeString, xxx)
{
	time_t timer = time(NULL);
	strcpy(gmbuff, asctime(gmtime(&timer)));
	//return asctime(gmtime(&timer)));
	return gmbuff;
}

method(MCClock, printTime, xxx)
{
	printf("\n%s", asctime(&this->rawtime));
}

method(MCClock, printCurrentTime, xxx)
{
	time_t timer = time(NULL);
	printf("%s", asctime(localtime(&timer)));
}

method(MCClock, printCurrentGMTTime, xxx)
{
	time_t timer = time(NULL);
	printf("%s", asctime(gmtime(&timer)));
}

constructor(MCClock, xxx)
{
	link_class(MCClock, MCObject, nil)
	{
		have_method(MCClock, setTimeToNow);
		have_method(MCClock, setTime);
		have_method(MCClock, adjustTime);

		have_method(MCClock, setRawtime);
		have_method(MCClock, setRawtimeFields);

		have_method(MCClock, getTime);
		have_method(MCClock, getRawtime);
		have_method(MCClock, getTimeByString);

		have_method(MCClock, getCPUClocksPerSecond);
		have_method(MCClock, getCPUClocksSinceStart);
		have_method(MCClock, getCurrentTimeString);
		have_method(MCClock, getCurrentGMTTimeString);

		have_method(MCClock, printTime);
		have_method(MCClock, printCurrentTime);
		have_method(MCClock, printCurrentGMTTime);
	}

	return this;
}

char* MCClock_rawtime2String(time_t* timeval)
{
	return ctime(timeval);
}

char* MCClock_settableTime2String(struct tm *tm)
{
	return asctime(tm);
}

struct tm* MCClock_rawtime2SettableTimeGMT(time_t* timeval)
{
	return gmtime(timeval);
}

struct tm* MCClock_rawtime2SettableTimeLocal(time_t* timeval)
{
	return localtime(timeval);
}



