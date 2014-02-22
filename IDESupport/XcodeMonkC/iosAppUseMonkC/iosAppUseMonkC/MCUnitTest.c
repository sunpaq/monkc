#include "MCUnitTest.h"
/* Assert Functions */

void assertYES(int expression) throws(MCAssertYESException)
{
	if ((expression)!=1)
		throw(MCAssertYESException);
}

void assertNO(int expression) throws(MCAssertNOException)
{
	if ((expression)!=0)
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

void assertSame(mo obj1, mo obj2) throws(MCAssertSameException)
{
	if (obj1!=obj2)
		throw(MCAssertSameException);
}

void assertNotSame(mo obj1, mo obj2) throws(MCAssertNotSameException)
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
	binding(MCUnitTestCase, MCUnitTestCase*, initWithTestResult, MCUnitTestResult* resultRef);
	binding(MCUnitTestCase, void, bye, xxx);
	binding(MCUnitTestCase, void, setUp, xxx);
	binding(MCUnitTestCase, void, tearDown, xxx);
	binding(MCUnitTestCase, void, runTests, xxx);
	binding(MCUnitTestCase, void, runATestMethod, char* errmsg);
	return claz;
}

initer(MCUnitTestCase)
{
	obj->next_case = nil;
	return obj;
}

method(MCUnitTestCase, MCUnitTestCase*, initWithTestResult, MCUnitTestResult* resultRef)
{
	if(resultRef!=nil){
		retain(resultRef);
		obj->unitTestResultRef = resultRef;
	}else{
		obj->unitTestResultRef = nil;
	}
	return obj;
}

method(MCUnitTestCase, void, bye, xxx)
{
	if(obj->unitTestResultRef!=nil)
		release(&(obj->unitTestResultRef));
}

method(MCUnitTestCase, void, setUp, xxx)
{
	//set up fixture
	runtime_log("----MCUnitTestCase setUp\n");
}

method(MCUnitTestCase, void, tearDown, xxx)
{
	//tear down fixture
	runtime_log("----MCUnitTestCase tearDown\n");
}

static void runMethodByPointer(MCUnitTestCase* obj, mc_hashitem* amethod)
{
	ff(obj, setUp, nil);
	runtime_log("%s\n", "runMethodByPointer start");

	try{
		_push_jump(_response_to(cast(mo, obj), amethod->key, 0), nil);
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
		error_log("testcase: %s at method: [%s]\n", obj->isa->item->key, amethod->key);
	}

	ff(obj, tearDown, nil);
}

method(MCUnitTestCase, void, runTests, xxx)
{
	runtime_log("%s\n", "MCUnitTestCase runTests");
	unsigned i;
	unsigned bye_key = hash("bye");
	unsigned setUp_key = hash("setUp");
	unsigned tearDown_key = hash("tearDown");

	mc_hashitem* amethod;
	if(obj==nil || obj->isa==nil)
		return;

	runtime_log("%s\n", "MCUnitTestCase runTests before for loop");
	for (i = 0; i < get_tablesize(obj->isa->table->level); i++)
	{
		//runtime_log("MCUnitTestCase runTests in for loop index:[%d]\n", i);
		amethod = obj->isa->table->items[i];
		if(amethod!=nil 
		&& amethod->value!=nil 
		&& amethod->key!=nil
		&& i!=bye_key
		&& i!=setUp_key
		&& i!=tearDown_key){
			runtime_log("%s\n", "MCUnitTestCase runTests hit a matched method");
			if(obj==nil || amethod==nil){
				error_log("MCUnitTestCase runTests this pointer is nil\n");
			}

			runMethodByPointer(obj, amethod);
		}
	}
}

method(MCUnitTestCase, void, runATestMethod, char* methodName)
{
	runMethodByPointer(obj, obj->isa->table->items[hash(methodName)]);
}

/* Test Suite */

loader(MCUnitTestSuite)
{
	binding(MCUnitTestSuite, void, bye, xxx);
	binding(MCUnitTestSuite, void, addTestCase, MCUnitTestCase* tcase);
	binding(MCUnitTestSuite, void, runTestCases, xxx);
	return claz;
}

initer(MCUnitTestSuite)
{
	obj->first_case = nil;
    obj->last_case_p = &(obj->first_case);
	obj->test_case_count = 0;
	obj->next_suite = nil;
	return obj;
}

method(MCUnitTestSuite, void, bye, xxx)
{
	MCUnitTestCase *iter, *save;
	for(iter=obj->first_case; (save=iter)!=nil; release(save))
		iter = iter->next_case;
}

method(MCUnitTestSuite, void, addTestCase, MCUnitTestCase* volatile tcase)
{
	retain(tcase);
    *(obj->last_case_p) = tcase;
    obj->last_case_p = cast(MCUnitTestCase**, &tcase);
	obj->test_case_count++;
}

method(MCUnitTestSuite, void, runTestCases, xxx)
{
	runtime_log("%s\n", "MCUnitTestSuite runTestCases");
	MCUnitTestCase *iter = nil;
	for(iter=obj->first_case; iter!=nil; iter = iter->next_case)
		call(iter, MCUnitTestCase, runTests, nil);
}

/* Test Result */

// #ifndef _MCUnitTestResult
// #define _MCUnitTestResult _MCObject;\


loader(MCUnitTestResult)
{
	binding(MCUnitTestResult, void, bye, xxx);
	binding(MCUnitTestResult, void, addSuccessInfo, char* succinfo);
	binding(MCUnitTestResult, void, addFailInfo, char* failinfo);
	return claz;
}

initer(MCUnitTestResult)
{
	//nothing to init
	return obj;
}

method(MCUnitTestResult, void, bye, xxx)
{
	//nothing to clean
}

method(MCUnitTestResult, void, addSuccessInfo, char* succinfo)
{
	//
}

method(MCUnitTestResult, void, addFailInfo, char* failinfo)
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
	binding(MCUnitTestRunner, void, bye, xxx);
	binding(MCUnitTestRunner, void, addTestSuite, MCUnitTestSuite* testSuite);
	binding(MCUnitTestRunner, void, runTestSuites, xxx);
	return claz;
}

initer(MCUnitTestRunner)
{
	obj->first_suite = nil;
	obj->test_suite_count = 0;
	return obj;
}

method(MCUnitTestRunner, void, bye, xxx)
{
	MCUnitTestSuite *iter, *save;
	for(iter=obj->first_suite; (save=iter)!=nil; release(save))
		iter = iter->next_suite;
}

method(MCUnitTestRunner, void, addTestSuite, MCUnitTestSuite* testSuite)
{
	retain(testSuite);
	MCUnitTestSuite **iter;
	for(iter=&(obj->first_suite); (*iter)!=nil; iter=&((*iter)->next_suite)){}
	(*iter)=testSuite;
	obj->test_suite_count++;
}

method(MCUnitTestRunner, void, runTestSuites, xxx)
{
	runtime_log("%s\n", "MCUnitTestRunner runTestSuites");
	MCUnitTestSuite *iter;
	for(iter=obj->first_suite; iter!=nil; iter = iter->next_suite)
		call(iter, MCUnitTestSuite, runTestCases, nil);
}


