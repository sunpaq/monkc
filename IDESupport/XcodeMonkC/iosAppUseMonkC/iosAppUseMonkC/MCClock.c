#include "MCClock.h"

initer(MCClock)
{
	//nothing
	return obj;
}

loader(MCClock)
{
binding(MCClock, void, setTimeToNow, xxx);
binding(MCClock, 
void, setTime, int tm_sec, int tm_min, int tm_hour, 
			   int tm_mday, int tm_mon, int tm_year,
			   int tm_wday);
binding(MCClock, 
void, adjustTime, int tm_sec, int tm_min, int tm_hour, 
                  int tm_mday, int tm_mon, int tm_year,
                  int tm_wday);

binding(MCClock, void, setRawtime, struct tm rawtime_in);
binding(MCClock, 
void, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
					    int tm_mday, int tm_mon, int tm_year,
					    int tm_wday, int tm_yday, int tm_isdst);

binding(MCClock, void, getTime, time_t* const result);
binding(MCClock, void, getRawtime, struct tm* const result);
binding(MCClock, char*, getTimeByString, xxx);
binding(MCClock, void, getCPUClocksPerSecond, clock_t* const result);
binding(MCClock, void, getCPUClocksSinceStart, clock_t* const result);
binding(MCClock, char*, getCurrentTimeString, xxx);//retrun the same format as asctime: Sun Sep 16 01:03:52 1973\n\0
binding(MCClock, char*, getCurrentGMTTimeString, xxx);
binding(MCClock, void, printTime, xxx);
binding(MCClock, void, printCurrentTime, xxx);
binding(MCClock, void, printCurrentGMTTime, xxx);
return claz;
}

method(MCClock, MCClock*, setTimeToNow, xxx)
{
	time_t timer = time(NULL);
	obj->rawtime = *localtime(&timer);
    return obj;
}

method(MCClock, 
void, setTime, int tm_sec, int tm_min, int tm_hour, 
			   int tm_mday, int tm_mon, int tm_year,
			   int tm_wday)
{
	if(tm_sec!=no_change) obj->rawtime.tm_sec = tm_sec;
	if(tm_min!=no_change) obj->rawtime.tm_min = tm_min;
	if(tm_hour!=no_change) obj->rawtime.tm_hour = tm_hour;
	if(tm_mday!=no_change) obj->rawtime.tm_mday = tm_mday;
	if(tm_mon!=no_change) obj->rawtime.tm_mon = tm_mon;
	int year = tm_year-1900;
	if(tm_year!=no_change) obj->rawtime.tm_year = year;
	if(tm_wday!=no_change) obj->rawtime.tm_wday = tm_wday;
}

method(MCClock, 
void, adjustTime, int tm_sec, int tm_min, int tm_hour, 
                  int tm_mday, int tm_mon, int tm_year,
                  int tm_wday)
{
	if(tm_sec!=no_change) obj->rawtime.tm_sec += tm_sec;
	if(tm_min!=no_change) obj->rawtime.tm_min += tm_min;
	if(tm_hour!=no_change) obj->rawtime.tm_hour += tm_hour;
	if(tm_mday!=no_change) obj->rawtime.tm_mday += tm_mday;
	if(tm_mon!=no_change) obj->rawtime.tm_mon += tm_mon;
	if(tm_year!=no_change) obj->rawtime.tm_year += tm_year;
	if(tm_wday!=no_change) obj->rawtime.tm_wday += tm_wday;
}

method(MCClock, void, setRawtime, struct tm rawtime_in)
{
	obj->rawtime = rawtime_in;
}

method(MCClock, 
void, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
						int tm_mday, int tm_mon, int tm_year,
						int tm_wday, int tm_yday, int tm_isdst)
{
	if(tm_sec!=no_change)obj->rawtime.tm_sec = tm_sec;
	if(tm_sec!=no_change)obj->rawtime.tm_min = tm_min;
	if(tm_sec!=no_change)obj->rawtime.tm_hour = tm_hour;
	//
	if(tm_sec!=no_change)obj->rawtime.tm_mday = tm_mday;
	if(tm_sec!=no_change)obj->rawtime.tm_mon = tm_mon;
	if(tm_sec!=no_change)obj->rawtime.tm_year = tm_year-1900;
	//
	if(tm_sec!=no_change)obj->rawtime.tm_wday = tm_wday;
	if(tm_sec!=no_change)obj->rawtime.tm_yday = tm_yday;
	if(tm_sec!=no_change)obj->rawtime.tm_isdst = tm_isdst;
}

method(MCClock, 
void, getTime, time_t* const result)
{
	*result = mktime(&(obj->rawtime));
}

method(MCClock, void, getRawtime, struct tm* const result)
{
	*result = obj->rawtime;
}

static char strbuff[50];
method(MCClock, char*, getTimeByString, xxx)
{
	strcpy(strbuff, asctime(&(obj->rawtime)));
	return strbuff;
}

method(MCClock, void, getCPUClocksPerSecond, clock_t* const result)
{
	*result = CLOCKS_PER_SEC;
}

method(MCClock, void, getCPUClocksSinceStart, clock_t* const result)
{
	*result = clock();
}

static char buff[50];
method(MCClock, char*, getCurrentTimeString, xxx)
{
	time_t timer = time(NULL);
	strcpy(buff, asctime(localtime(&timer)));
	//return asctime(localtime(&timer)));
	return buff;
}

static char* gmbuff[50];
method(MCClock, char*, getCurrentGMTTimeString, xxx)
{
	time_t timer = time(NULL);
	strcpy(gmbuff[0], asctime(gmtime(&timer)));
	//return asctime(gmtime(&timer)));
	return gmbuff[0];
}

method(MCClock, void, printTime, xxx)
{
	printf("\n%s", asctime(&obj->rawtime));
}

method(MCClock, void, printCurrentTime, xxx)
{
	time_t timer = time(NULL);
	printf("%s", asctime(localtime(&timer)));
}

method(MCClock, void, printCurrentGMTTime, xxx)
{
	time_t timer = time(NULL);
	printf("%s", asctime(gmtime(&timer)));
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