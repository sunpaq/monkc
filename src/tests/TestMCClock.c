#include "TestMCClock.h"
static const char* LOG_TAG = "TestMCClock";

loader(TestMCClock)
{
	binding(TestMCClock, void, setTimeToNow, xxx);
	binding(TestMCClock, void, setTime, xxx);
	binding(TestMCClock, void, adjustTime, xxx);
	binding(TestMCClock, void, setRawtime, xxx);
	binding(TestMCClock, void, setRawtimeFields, xxx);

	binding(TestMCClock, void, getTime, xxx);
	binding(TestMCClock, void, getRawtime, xxx);
	binding(TestMCClock, void, getTimeByString, xxx);
	binding(TestMCClock, void, getCPUClocksPerSecond, xxx);
	binding(TestMCClock, void, getCPUClocksSinceStart, xxx);
	binding(TestMCClock, void, getCurrentTimeString, xxx);
	binding(TestMCClock, void, getCurrentGMTTimeString, xxx);

	binding(TestMCClock, void, printTime, xxx);
	binding(TestMCClock, void, printCurrentTime, xxx);
	binding(TestMCClock, void, printCurrentGMTTime, xxx);

	//override
	override(TestMCClock, void, setUp, xxx);
	override(TestMCClock, void, tearDown, xxx);
}


initer(TestMCClock)
{
	this->super = new(MCUnitTestCase);
	this->toBeTest = nil;
}

//override
method(TestMCClock, void, setUp, xxx)
{
	call(this, MCUnitTestCase, setUp, nil);
	if(this->toBeTest==nil)
		this->toBeTest = new(MCClock);
}

method(TestMCClock, void, tearDown, xxx)
{
	call(this, MCUnitTestCase, tearDown, nil);
	if(this->toBeTest!=nil)
		release(&(this->toBeTest));
}

method(TestMCClock, void, setTimeToNow, xxx)
{
	debug_logt(LOG_TAG, "TestMCClock setTimeToNow\n");
	ff(this->toBeTest, setTimeToNow, nil);
	assertNotNil(this->toBeTest);
	//for test, we need time output
	ff(this->toBeTest, printTime, nil);
}

method(TestMCClock, void, setTime, xxx)
{
	debug_logt(LOG_TAG, "TestMCClock setTime\n");
	ff(this->toBeTest, setTime, 59, 10, 21, 29, MAR, 2013, FRI);
	assertNotNil(this->toBeTest);
	//for test, we need time output
	ff(this->toBeTest, printTime, nil);
}

method(TestMCClock, void, adjustTime, xxx)
{

}

method(TestMCClock, void, setRawtime, xxx)
{

}

method(TestMCClock, void, setRawtimeFields, xxx)
{

}

method(TestMCClock, void, getTime, xxx)
{

}

method(TestMCClock, void, getRawtime, xxx)
{

}

method(TestMCClock, void, getTimeByString, xxx)
{

}

method(TestMCClock, void, getCPUClocksPerSecond, xxx)
{

}

method(TestMCClock, void, getCPUClocksSinceStart, xxx)
{

}

method(TestMCClock, void, getCurrentTimeString, xxx)
{

}

method(TestMCClock, void, getCurrentGMTTimeString, xxx)
{

}

method(TestMCClock, void, printTime, xxx)
{

}

method(TestMCClock, void, printCurrentTime, xxx)
{

}

method(TestMCClock, void, printCurrentGMTTime, xxx)
{

}

