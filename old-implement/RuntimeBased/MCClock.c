#include "MCClock.h"

method_imp(MCClock, getCurrentTimeString, xxx)
{
	time_t timer;
	timer=time(NULL);
	return asctime(localtime(&timer));
}

