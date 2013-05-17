#include "MCUnitTest.h"
/* Assert Functions */

void assertYES(int expression) throws(MCAssertYESException)
{
	if ((expression)!=YES)
		throw(MCAssertYESException);
}

void assertNO(int expression) throws(MCAssertNOException)
{
	if ((expression)!=NO)
		throw(MCAssertNOException);
}

void assertNil(void* ptr) throws(MCAssertNilException)
{
	if (ptr!=nil)
		throw(MCAssertNilException);
}

void assertNotNil(void* ptr) throws(MCAssertNotNilException)
{
	if (ptr==nil)
		throw(MCAssertNotNilException);
}

void assertSame(id obj1, id obj2) throws(MCAssertSameException)
{
	if (obj1!=obj2)
		throw(MCAssertSameException);
}

void assertNotSame(id obj1, id obj2) throws(MCAssertNotSameException)
{
	if (obj1==obj2)
		throw(MCAssertNotSameException);
}

void assertEquals(int exp1, int exp2) throws(MCAssertEqualsException)
{
	if ((exp1)!=(exp2))
		throw(MCAssertEqualsException);
}

void fail(char* message)
{
	printf("%s\n", message);
	abort();
}

/* Test Case */

constructor(MCUnitTestCase, MCUnitTestResult* resultRef)
{
	link_class(MCUnitTestCase, MCObject, nil)
	{
		binding(MSNA, MCUnitTestCase, bye, xxx);
		binding(MSNA, MCUnitTestCase, setUp, xxx);
		binding(MSNA, MCUnitTestCase, tearDown, xxx);
		binding(MSNA, MCUnitTestCase, runTests, xxx);
		binding(MSNA, MCUnitTestCase, runATestMethod, char* errmsg);
	}

	retain(resultRef);
	this->unitTestResultRef = resultRef;
	this->next_case = nil;
	return this;
}

method(MCUnitTestCase, bye, xxx)
{
	relnil(this->unitTestResultRef);
}

method(MCUnitTestCase, setUp, xxx)
{
	//set up fixture
	printf("MCUnitTestCase setUp\n");
}

method(MCUnitTestCase, tearDown, xxx)
{
	//tear down fixture
	printf("MCUnitTestCase tearDown\n");
}

static void runMethodByKey(MCUnitTestCase* this, unsigned key)
{
	call(this, MCUnitTestCase, setUp, nil);

	try{
		_ff(this, key, nil);
		//if exception generated, this line will never be reached
	}
	catch(MCAssertYESException){
		printf("MCAssertNOException\n");
	}
	catch(MCAssertNOException){
		printf("MCAssertNOException\n");
	}
	catch(MCAssertNilException){
		printf("MCAssertNilException\n");
	}
	catch(MCAssertNotNilException){
		printf("MCAssertNotNilException\n");
	}
	catch(MCAssertSameException){
		printf("MCAssertSameException\n");
	}
	catch(MCAssertNotSameException){
		printf("MCAssertNotSameException\n");
	}
	catch(MCAssertEqualsException){
		printf("MCAssertEqualsException\n");
	}
	finally{
		printf("testcase: %s at method: [%d]\n", this->isa->name, key);
	}

	call(this, MCUnitTestCase, tearDown, nil);
}

method(MCUnitTestCase, runTests, xxx)
{
	printf("%s\n", "MCUnitTestCase runTests");
	unsigned i;
	for (i = 0; i < MAX_METHOD_NUM; i++)
	{
		//(*this->method_list[i])();
		if(this->isa->method_list[i]!=nil)runMethodByKey(this, i);
	}
}

method(MCUnitTestCase, runATestMethod, char* methodName)
{
	runMethodByKey(this, MK(methodName));
}

/* Test Suite */

constructor(MCUnitTestSuite, xxx)
{
	link_class(MCUnitTestSuite, MCObject, nil)
	{
		binding(MSNA, MCUnitTestSuite, bye, xxx);
		binding(MS(2,P,P), MCUnitTestSuite, addTestCase, MCUnitTestCase* tcase);
		binding(MSNA, MCUnitTestSuite, runTestCases, xxx);
	}

	this->first_case = nil;
	this->test_case_count = 0;
	this->next_suite = nil;

	return this;
}

method(MCUnitTestSuite, bye, xxx)
{
	MCUnitTestCase *iter, *save;
	for(iter=this->first_case; (save=iter)!=nil; release(save))
		iter = iter->next_case;
}

method(MCUnitTestSuite, addTestCase, MCUnitTestCase* tcase)
{
	retain(tcase);
	MCUnitTestCase **iter;
	for(iter=&this->first_case; *iter!=nil; iter=&((*iter)->next_case)){}
	*iter=tcase;
	this->test_case_count++;
}

method(MCUnitTestSuite, runTestCases, xxx)
{
	printf("%s\n", "MCUnitTestSuite runTestCases");
	MCUnitTestCase *iter;
	for(iter=this->first_case; iter!=nil; iter = iter->next_case)
		call(iter, MCUnitTestCase, runTests, nil);
}

/* Test Result */

// #ifndef _MCUnitTestResult
// #define _MCUnitTestResult _MCObject;\

constructor(MCUnitTestResult, xxx)
{
	link_class(MCUnitTestResult, MCObject, nil)
	{
		binding(MSNA, MCUnitTestResult, bye, xxx);
		binding(MSNA, MCUnitTestResult, addSuccessInfo, char* succinfo);
		binding(MSNA, MCUnitTestResult, addFailInfo, char* failinfo);
	}

	return this;
}

method(MCUnitTestResult, bye, xxx)
{
	//
}

method(MCUnitTestResult, addSuccessInfo, char* succinfo)
{
	//
}

method(MCUnitTestResult, addFailInfo, char* failinfo)
{
	//
}

/* Test Runner */

// #ifndef _MCUnitTestRunner
// #define _MCUnitTestRunner _MCObject;\
// 	MCUnitTestResult* unitTestResult;\
// 	MCUnitTestSuite* first_suite;\
// 	int test_suite_count;\

// class(MCUnitTestRunner);
constructor(MCUnitTestRunner, xxx)
{
	link_class(MCUnitTestRunner, MCObject, nil)
	{
		binding(MSNA, MCUnitTestRunner, bye, xxx);
		binding(MS(2,P,P), MCUnitTestRunner, addTestSuite, MCUnitTestSuite* testSuite);
		binding(MSNA, MCUnitTestRunner, runTestSuites, xxx);
	}

	this->first_suite = nil;
	this->test_suite_count = 0;

	return this;
}

method(MCUnitTestRunner, bye, xxx)
{
	MCUnitTestSuite *iter, *save;
	for(iter=this->first_suite; (save=iter)!=nil; release(save))
		iter = iter->next_suite;
}

method(MCUnitTestRunner, addTestSuite, MCUnitTestSuite* testSuite)
{
	retain(testSuite);
	MCUnitTestSuite **iter;
	for(iter=&(this->first_suite); (*iter)!=nil; iter=&((*iter)->next_suite)){}
	(*iter)=testSuite;
	this->test_suite_count++;
}

method(MCUnitTestRunner, runTestSuites, xxx)
{
	printf("%s\n", "MCUnitTestRunner runTestSuites");
	MCUnitTestSuite *iter;
	for(iter=this->first_suite; iter!=nil; iter = iter->next_suite)
		call(iter, MCUnitTestSuite, runTestCases, nil);
}


