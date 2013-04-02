#include "MCContext.h"
#include "MCUnitTest.h"
#include "TestMCRuntime.h"
#include "TestMCClock.h"

int main(int argc, char const *argv[])
{
	mc_init();

	//while(1){
		MCUnitTestRunner* runner = new(MCUnitTestRunner, nil);
		MCUnitTestSuite* suite = new(MCUnitTestSuite, nil);
		
		ff(suite, addTestCase, new_anony(TestMCRuntime, nil));
		ff(suite, addTestCase, new_anony(TestMCClock, nil));
		//ff(suite, addTestCase, new_anony(MyTestCase1, nil));

		ff(runner, addTestSuite, suite);
		ff(runner, runTestSuites, nil);

		relnil(runner);
		relnil(suite);

		//sleep(5);
	//}

	mc_end();
	return 0;
}
