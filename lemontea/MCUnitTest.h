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
	
class(MCUnitTestResult, MCObject);

method(MCUnitTestResult, void, bye, voida);
method(MCUnitTestResult, void, addSuccessInfo, char* succinfo);
method(MCUnitTestResult, void, addFailInfo, char* failinfo);
#endif

/* Test Case */

#ifndef MCUnitTestCase_
#define MCUnitTestCase_ 

class(MCUnitTestCase, MCObject,
	MCUnitTestResult* unitTestResultRef;
	struct MCUnitTestCaseStruct* next_case;
);

method(MCUnitTestCase, MCUnitTestCase*, initWithTestResult, MCUnitTestResult* resultRef);
method(MCUnitTestCase, void, bye, voida);
method(MCUnitTestCase, void, setUp, voida);
method(MCUnitTestCase, void, tearDown, voida);
method(MCUnitTestCase, void, runTests, voida);
method(MCUnitTestCase, void, runATestMethod, char* methodName);
#endif

/* Test Suite */

#ifndef MCUnitTestSuite_
#define MCUnitTestSuite_

class(MCUnitTestSuite, MCObject,
	MCUnitTestCase *first_case;
    MCUnitTestCase **last_case_p;
	int test_case_count;
	struct MCUnitTestSuiteStruct* next_suite;
);

method(MCUnitTestSuite, void, bye, voida);
method(MCUnitTestSuite, void, addTestCase, MCUnitTestCase* volatile tcase);
method(MCUnitTestSuite, void, runTestCases, voida);
#endif

/* Test Runner */

#ifndef MCUnitTestRunner_
#define MCUnitTestRunner_

class(MCUnitTestRunner, MCObject,
	MCUnitTestResult* unitTestResult;
	MCUnitTestSuite* first_suite;
	int test_suite_count;
);

method(MCUnitTestRunner, void, bye, voida);
method(MCUnitTestRunner, void, addTestSuite, MCUnitTestSuite* testSuite);
method(MCUnitTestRunner, void, runTestSuites, voida);

#endif