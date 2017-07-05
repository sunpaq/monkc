#include "MCClock.h"

oninit(MCClock)
{
    if (init(MCObject)) {
        var(currentTimeBuff) = (char*)malloc(sizeof(char) * LINE_MAX);
        var(currentGMTBuff) = (char*)malloc(sizeof(char) * LINE_MAX);
        return obj;
    }else{
        return mull;
    }
}

method(MCClock, void, bye, voida)
{
    free(var(currentTimeBuff));
    free(var(currentGMTBuff));
}

method(MCClock, MCClock*, setTimeToNow, voida)
{
	time_t timer = time(NULL);
	obj->rawtime = *localtime(&timer);
    return obj;
}

method(MCClock, void, setTime, int tm_sec, int tm_min, int tm_hour,
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

method(MCClock, void, adjustTime, int tm_sec, int tm_min, int tm_hour,
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

method(MCClock, void, setRawtimeFields, int tm_sec, int tm_min, int tm_hour, 
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

method(MCClock, void, getTime, time_t* const result)
{
	*result = mktime(&(obj->rawtime));
}

method(MCClock, void, getRawtime, struct tm* const result)
{
	*result = obj->rawtime;
}

method(MCClock, char*, getTimeByString, voida)
{
	strcpy((char*)obj->currentTimeBuff, asctime(&(obj->rawtime)));
	return (char*)obj->currentTimeBuff;
}

method(MCClock, void, getCPUClocksPerSecond, clock_t* const result)
{
	*result = CLOCKS_PER_SEC;
}

method(MCClock, void, getCPUClocksSinceStart, clock_t* const result)
{
	*result = clock();
}

method(MCClock, char*, getCurrentTimeString, voida)
{
	time_t timer = time(NULL);
	strcpy((char*)obj->currentTimeBuff, asctime(localtime(&timer)));
	return (char*)obj->currentTimeBuff;
}

method(MCClock, char*, getCurrentGMTTimeString, voida)
{
	time_t timer = time(NULL);
	strcpy((char*)obj->currentGMTBuff, asctime(gmtime(&timer)));
	return (char*)obj->currentGMTBuff;
}

method(MCClock, void, printTime, voida)
{
	printf("\n%s", asctime(&obj->rawtime));
}

method(MCClock, void, printCurrentTime, voida)
{
	time_t timer = time(NULL);
	printf("%s", asctime(localtime(&timer)));
}

method(MCClock, void, printCurrentGMTTime, voida)
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

onload(MCClock)
{
    if (load(MCObject)) {
    	binding(MCClock, void, bye, voida);
        binding(MCClock, void, setTimeToNow);
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
        binding(MCClock, char*, getTimeByString);
        binding(MCClock, void, getCPUClocksPerSecond, clock_t* const result);
        binding(MCClock, void, getCPUClocksSinceStart, clock_t* const result);
        binding(MCClock, char*, getCurrentTimeString);//retrun the same format as asctime: Sun Sep 16 01:03:52 1973\n\0
        binding(MCClock, char*, getCurrentGMTTimeString);
        binding(MCClock, void, printTime);
        binding(MCClock, void, printCurrentTime);
        binding(MCClock, void, printCurrentGMTTime);
        return cla;
    }else{
        return mull;
    }
}
