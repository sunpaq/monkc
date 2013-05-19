#include "TestMCClock.h"
static const char* LOG_TAG = "TestMCClock";
constructor(TestMCClock, xxx)
{
	link_class(TestMCClock, MCUnitTestCase, nil)
	{
		binding(TestMCClock, setTimeToNow, xxx);
		binding(TestMCClock, setTime, xxx);
		binding(TestMCClock, adjustTime, xxx);
		binding(TestMCClock, setRawtime, xxx);
		binding(TestMCClock, setRawtimeFields, xxx);

		binding(TestMCClock, getTime, xxx);
		binding(TestMCClock, getRawtime, xxx);
		binding(TestMCClock, getTimeByString, xxx);
		binding(TestMCClock, getCPUClocksPerSecond, xxx);
		binding(TestMCClock, getCPUClocksSinceStart, xxx);
		binding(TestMCClock, getCurrentTimeString, xxx);
		binding(TestMCClock, getCurrentGMTTimeString, xxx);

		binding(TestMCClock, printTime, xxx);
		binding(TestMCClock, printCurrentTime, xxx);
		binding(TestMCClock, printCurrentGMTTime, xxx);

		//override
		override(TestMCClock, setUp, xxx);
		override(TestMCClock, tearDown, xxx);
	}

	this->toBeTest = nil;

	return this;
}

//override
method(TestMCClock, setUp, xxx)
{
	call(this, MCUnitTestCase, setUp, nil);
	if(this->toBeTest==nil)
		this->toBeTest = new(MCClock, nil);
}

method(TestMCClock, tearDown, xxx)
{
	call(this, MCUnitTestCase, tearDown, nil);
	if(this->toBeTest!=nil)
		relnil(this->toBeTest);
}

method(TestMCClock, setTimeToNow, xxx)
{
	debug_logt(LOG_TAG, "TestMCClock setTimeToNow\n");
	ff(this->toBeTest, setTimeToNow, nil);
	assertNotNil(this->toBeTest);
	//for test, we need time output
	ff(this->toBeTest, printTime, nil);
}

method(TestMCClock, setTime, xxx)
{
	debug_logt(LOG_TAG, "TestMCClock setTime\n");
	ff(this->toBeTest, setTime, 59, 10, 21, 29, MAR, 2013, FRI);
	assertNotNil(this->toBeTest);
	//for test, we need time output
	ff(this->toBeTest, printTime, nil);
}

method(TestMCClock, adjustTime, xxx)
{

}

method(TestMCClock, setRawtime, xxx)
{

}

method(TestMCClock, setRawtimeFields, xxx)
{

}

method(TestMCClock, getTime, xxx)
{

}

method(TestMCClock, getRawtime, xxx)
{

}

method(TestMCClock, getTimeByString, xxx)
{

}

method(TestMCClock, getCPUClocksPerSecond, xxx)
{

}

method(TestMCClock, getCPUClocksSinceStart, xxx)
{

}

method(TestMCClock, getCurrentTimeString, xxx)
{

}

method(TestMCClock, getCurrentGMTTimeString, xxx)
{

}

method(TestMCClock, printTime, xxx)
{

}

method(TestMCClock, printCurrentTime, xxx)
{

}

method(TestMCClock, printCurrentGMTTime, xxx)
{

}

