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
	error_log("%s\n", message);
	abort();
}

/* Test Case */


loader(MCUnitTestCase)
{
	binding(MCUnitTestCase, initWithTestResult, MCUnitTestResult* resultRef);
	binding(MCUnitTestCase, bye, xxx);
	binding(MCUnitTestCase, setUp, xxx);
	binding(MCUnitTestCase, tearDown, xxx);
	binding(MCUnitTestCase, runTests, xxx);
	binding(MCUnitTestCase, runATestMethod, char* errmsg);
}

initer(MCUnitTestCase)
{
	this->next_case = nil;
}

method(MCUnitTestCase, initWithTestResult, MCUnitTestResult* resultRef)
{
	if(resultRef!=nil){
		retain(resultRef);
		this->unitTestResultRef = resultRef;
	}else{
		this->unitTestResultRef = nil;
	}
	return this;
}

method(MCUnitTestCase, bye, xxx)
{
	if(this->unitTestResultRef!=nil)
		release(&(this->unitTestResultRef));
}

method(MCUnitTestCase, setUp, xxx)
{
	//set up fixture
	runtime_log("----MCUnitTestCase setUp\n");
}

method(MCUnitTestCase, tearDown, xxx)
{
	//tear down fixture
	runtime_log("----MCUnitTestCase tearDown\n");
}

static void runMethodByPointer(MCUnitTestCase* this, mc_hashitem* amethod)
{
	ff(this, setUp, nil);
	runtime_log("%s\n", "runMethodByPointer start");

	try{
		_push_jump(_response_to(this, amethod->key), nil);
		//if exception generated, this line will never be reached
	}
	catch(MCAssertYESException){
		error_log("MCAssertNOException\n");
	}
	catch(MCAssertNOException){
		error_log("MCAssertNOException\n");
	}
	catch(MCAssertNilException){
		error_log("MCAssertNilException\n");
	}
	catch(MCAssertNotNilException){
		error_log("MCAssertNotNilException\n");
	}
	catch(MCAssertSameException){
		error_log("MCAssertSameException\n");
	}
	catch(MCAssertNotSameException){
		error_log("MCAssertNotSameException\n");
	}
	catch(MCAssertEqualsException){
		error_log("MCAssertEqualsException\n");
	}
	finally{
		error_log("testcase: %s at method: [%s]\n", this->isa->item->key, amethod->key);
	}

	ff(this, tearDown, nil);
}

method(MCUnitTestCase, runTests, xxx)
{
	runtime_log("%s\n", "MCUnitTestCase runTests");
	unsigned i;
	unsigned bye_key = hash("bye");
	unsigned setUp_key = hash("setUp");
	unsigned tearDown_key = hash("tearDown");

	mc_hashitem* amethod;
	if(this==nil || this->isa==nil)
		return;

	runtime_log("%s\n", "MCUnitTestCase runTests before for loop");
	for (i = 0; i < get_tablesize(this->isa->table->level); i++)
	{
		//runtime_log("MCUnitTestCase runTests in for loop index:[%d]\n", i);
		amethod = this->isa->table->items[i];
		if(amethod!=nil 
		&& amethod->value!=nil 
		&& amethod->key!=nil
		&& i!=bye_key
		&& i!=setUp_key
		&& i!=tearDown_key){
			runtime_log("%s\n", "MCUnitTestCase runTests hit a matched method");
			if(this==nil || amethod==nil){
				error_log("MCUnitTestCase runTests this pointer is nil\n");
			}

			runMethodByPointer(this, amethod);
		}
	}
}

method(MCUnitTestCase, runATestMethod, char* methodName)
{
	runMethodByPointer(this, this->isa->table->items[hash(methodName)]);
}

/* Test Suite */

loader(MCUnitTestSuite)
{
	binding(MCUnitTestSuite, bye, xxx);
	binding(MCUnitTestSuite, addTestCase, MCUnitTestCase* tcase);
	binding(MCUnitTestSuite, runTestCases, xxx);
}

initer(MCUnitTestSuite)
{
	this->first_case = nil;
	this->test_case_count = 0;
	this->next_suite = nil;
}

method(MCUnitTestSuite, bye, xxx)
{
	MCUnitTestCase *iter, *save;
	for(iter=this->first_case; (save=iter)!=nil; release(save))
		iter = iter->next_case;
}

method(MCUnitTestSuite, addTestCase, MCUnitTestCase* volatile tcase)
{
	retain(tcase);
	MCUnitTestCase *iter = nil;
	for(iter=this->first_case; iter!=nil; iter=iter->next_case);
	iter=tcase;
	this->test_case_count++;
}

method(MCUnitTestSuite, runTestCases, xxx)
{
	runtime_log("%s\n", "MCUnitTestSuite runTestCases");
	MCUnitTestCase *iter = nil;
	for(iter=this->first_case; iter!=nil; iter = iter->next_case)
		call(iter, MCUnitTestCase, runTests, nil);
}

/* Test Result */

// #ifndef _MCUnitTestResult
// #define _MCUnitTestResult _MCObject;\


loader(MCUnitTestResult)
{
	binding(MCUnitTestResult, bye, xxx);
	binding(MCUnitTestResult, addSuccessInfo, char* succinfo);
	binding(MCUnitTestResult, addFailInfo, char* failinfo);
}

initer(MCUnitTestResult)
{
	//nothing to init
}

method(MCUnitTestResult, bye, xxx)
{
	//nothing to clean
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

loader(MCUnitTestRunner)
{
	binding(MCUnitTestRunner, bye, xxx);
	binding(MCUnitTestRunner, addTestSuite, MCUnitTestSuite* testSuite);
	binding(MCUnitTestRunner, runTestSuites, xxx);
}

initer(MCUnitTestRunner)
{
	this->first_suite = nil;
	this->test_suite_count = 0;
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
	runtime_log("%s\n", "MCUnitTestRunner runTestSuites");
	MCUnitTestSuite *iter;
	for(iter=this->first_suite; iter!=nil; iter = iter->next_suite)
		call(iter, MCUnitTestSuite, runTestCases, nil);
}


