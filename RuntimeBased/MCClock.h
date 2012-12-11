#ifndef __MCClock__
#define __MCClock__
#include <time.h>

MCInterface(MCClock, root);

MCInterfaceEnd(MCClock, init, xxx);
method(MCClock, getCurrentTimeString, xxx);

#endif