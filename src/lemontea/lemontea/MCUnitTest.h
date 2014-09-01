#include <assert.h>
#include "MCContext.h"
#include "MCException.h"
/* Assert Functions */
//void assert( int expression);
//all the exception will be catched inside the MCUnitTestCase, user should not catch them
void assertYES(int expression) throws(MCAssertYESException);
void assertNO(int expression) throws(MCAssertNOException);
void assertNil(void* ptr) throws(MCAssertNilException);
void assertNotNil(void* ptr) throws(MCAssertNotNilException);
void assertSame(mo obj1, mo obj2) throws(MCAssertSameException);
void assertNotSame(mo obj1, mo obj2) throws(MCAssertNotSameException);
void assertEquals(int exp1, int exp2) throws(MCAssertEqualsException);
void fail(char* message);

/* Test Result */

#ifndef MCUnitTestResult_
#define MCUnitTestResult_
	
monkc(MCUnitTestResult);
end(MCUnitTestResult);

method(MCUnitTestResult, void, bye, xxx);
method(MCUnitTestResult, void, addSuccessInfo, char* succinfo);
method(MCUnitTestResult, void, addFailInfo, char* failinfo);
#endif

/* Test Case */

#ifndef MCUnitTestCase_
#define MCUnitTestCase_ 

monkc(MCUnitTestCase);
	MCUnitTestResult* unitTestResultRef;
	struct MCUnitTestCase_struct* next_case;
end(MCUnitTestCase);

method(MCUnitTestCase, MCUnitTestCase*, initWithTestResult, MCUnitTestResult* resultRef);
method(MCUnitTestCase, void, bye, xxx);
method(MCUnitTestCase, void, setUp, xxx);
method(MCUnitTestCase, void, tearDown, xxx);
method(MCUnitTestCase, void, runTests, xxx);
method(MCUnitTestCase, void, runATestMethod, char* methodName);
#endif

/* Test Suite */

#ifndef MCUnitTestSuite_
#define MCUnitTestSuite_

monkc(MCUnitTestSuite);
	MCUnitTestCase *first_case;
    MCUnitTestCase **last_case_p;
	int test_case_count;
	struct MCUnitTestSuite_struct* next_suite;
end(MCUnitTestSuite);

method(MCUnitTestSuite, void, bye, xxx);
method(MCUnitTestSuite, void, addTestCase, MCUnitTestCase* volatile tcase);
method(MCUnitTestSuite, void, runTestCases, xxx);
#endif

/* Test Runner */

#ifndef MCUnitTestRunner_
#define MCUnitTestRunner_

monkc(MCUnitTestRunner);
	MCUnitTestResult* unitTestResult;
	MCUnitTestSuite* first_suite;
	int test_suite_count;
end(MCUnitTestRunner);

method(MCUnitTestRunner, void, bye, xxx);
method(MCUnitTestRunner, void, addTestSuite, MCUnitTestSuite* testSuite);
method(MCUnitTestRunner, void, runTestSuites, xxx);

#endif