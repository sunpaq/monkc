#include "MCContext.h"
#include "MCUnitTest.h"
#include "TestMCRuntime.h"
#include "TestMCClock.h"
#include "TestObjectManage.h"

int main(int argc, char const *argv[])
{
	LOG_LEVEL = MC_VERBOSE;
	//while(1){

	test_blockpool();



		MCUnitTestRunner* runner = new(MCUnitTestRunner);
		MCUnitTestSuite* suite = new(MCUnitTestSuite);
		
		ff(suite, addTestCase, new(TestMCRuntime));
		ff(suite, addTestCase, new(TestMCClock));

		ff(runner, addTestSuite, suite);
		ff(runner, runTestSuites, nil);

		release(runner);
		release(suite);



		//sleep(5);
	//}

	return 0;
}
