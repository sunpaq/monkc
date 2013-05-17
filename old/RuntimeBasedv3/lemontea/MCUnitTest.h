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
void assertSame(id obj1, id obj2) throws(MCAssertSameException);
void assertNotSame(id obj1, id obj2) throws(MCAssertNotSameException);
void assertEquals(int exp1, int exp2) throws(MCAssertEqualsException);
void fail(char* message);

/* Test Result */

#ifndef _MCUnitTestResult
#define _MCUnitTestResult _MCObject;\
	
class(MCUnitTestResult);
constructor(MCUnitTestResult, xxx);
method(MCUnitTestResult, bye, xxx);
method(MCUnitTestResult, addSuccessInfo, char* succinfo);
method(MCUnitTestResult, addFailInfo, char* failinfo);
#endif

/* Test Case */

#ifndef _MCUnitTestCase
#define _MCUnitTestCase _MCObject;\
	MCUnitTestResult* unitTestResultRef;\
	struct MCUnitTestCase_struct* next_case;\
	
class(MCUnitTestCase);
constructor(MCUnitTestCase, MCUnitTestResult* resultRef);
method(MCUnitTestCase, bye, xxx);
method(MCUnitTestCase, setUp, xxx);
method(MCUnitTestCase, tearDown, xxx);
method(MCUnitTestCase, runTests, xxx);
method(MCUnitTestCase, runATestMethod, char* methodName);
#endif

/* Test Suite */

#ifndef _MCUnitTestSuite
#define _MCUnitTestSuite _MCObject;\
	MCUnitTestCase *first_case;\
	int test_case_count;\
	struct MCUnitTestSuite_struct* next_suite;\ 

class(MCUnitTestSuite);
constructor(MCUnitTestSuite, xxx);
method(MCUnitTestSuite, bye, xxx);
method(MCUnitTestSuite, addTestCase, MCUnitTestCase* tcase);
method(MCUnitTestSuite, runTestCases, xxx);
#endif

/* Test Runner */

#ifndef _MCUnitTestRunner
#define _MCUnitTestRunner _MCObject;\
	MCUnitTestResult* unitTestResult;\
	MCUnitTestSuite* first_suite;\
	int test_suite_count;\

class(MCUnitTestRunner);
constructor(MCUnitTestRunner, xxx);
method(MCUnitTestRunner, bye, xxx);
method(MCUnitTestRunner, addTestSuite, MCUnitTestSuite* testSuite);
method(MCUnitTestRunner, runTestSuites, xxx);

#endif