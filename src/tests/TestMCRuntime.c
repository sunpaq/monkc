#include "TestMCRuntime.h"
static const char* LOG_TAG = "TestMCRuntime";


loader(TestMCRuntimeMockObj)
{
	binding(TestMCRuntimeMockObj, void, test_double, double a, double b, double c);
	binding(TestMCRuntimeMockObj, void, test_float, float a, float b, float c);
	binding(TestMCRuntimeMockObj, void, test_double_string, double a, char* b);
	binding(TestMCRuntimeMockObj, void, test_float_string, float a, char* b);
	binding(TestMCRuntimeMockObj, void, test_string_double, char* a, double b);
	binding(TestMCRuntimeMockObj, void, test_string_float, char* a, float b);

	return claz;
}

initer(TestMCRuntimeMockObj)
{
	//nothing to init
	return obj;
}


method(TestMCRuntimeMockObj, void, test_double, double a, double b, double c)
{
	debug_logt(LOG_TAG, "test_double a/b/c [%f/%f/%f]\n", a,b,c);
}

method(TestMCRuntimeMockObj, void, test_float, float a, float b, float c)
{
	debug_logt(LOG_TAG, "test_float a/b/c [%f/%f/%f]\n", a,b,c);
}

method(TestMCRuntimeMockObj, void, test_double_string, double a, char* b)
{
	debug_logt(LOG_TAG, "test_float a/b/c [%f/%f/%f]\n", a,b);
}

method(TestMCRuntimeMockObj, void, test_float_string, float a, char* b)
{
	debug_logt(LOG_TAG, "test_float_string a/b [%f/%s]\n", a,b);
}

method(TestMCRuntimeMockObj, void, test_string_double, char* a, double b)
{
	debug_logt(LOG_TAG, "test_string_double a/b [%s/%f]\n", a,b);
}

method(TestMCRuntimeMockObj, void, test_string_float, char* a, float b)
{
	debug_logt(LOG_TAG, "test_string_float a/b [%s/%f]\n", a,b);
}

/* the test case */

loader(TestMCRuntime)
{
	binding(TestMCRuntime, void, testArgument_float_all, xxx);
	binding(TestMCRuntime, void, testArgument_double_all, xxx);
	binding(TestMCRuntime, void, testArgument_double_string, xxx);
	//binding(TestMCRuntime, testArgument_float_string, xxx);
	binding(TestMCRuntime, void, testArgument_string_double, xxx);
	binding(TestMCRuntime, void, testArgument_string_float, xxx);
	//override
	override(TestMCRuntime, void, setUp, xxx);
	override(TestMCRuntime, void, tearDown, xxx);
	return claz;
}

initer(TestMCRuntime)
{
	obj->super = new(MCUnitTestCase);
	obj->mockobj = nil;
	return obj;
}
//override
method(TestMCRuntime, void, setUp, xxx)
{
	call(obj, MCUnitTestCase, setUp, nil);
	runtime_log("----TestMCRuntime setUp");
	obj->mockobj = new(TestMCRuntimeMockObj);
	if (obj->mockobj==nil){
		error_log("TestMCRuntime setUp failed");
		exit(-1);
	}
}

method(TestMCRuntime, void, tearDown, xxx)
{
	call(obj, MCUnitTestCase, tearDown, nil);
	release(&(obj->mockobj));
}

method(TestMCRuntime, void, testArgument_float_all, xxx)
{
	debug_logt(LOG_TAG, " testArgument_float_all\n");
	ff(obj->mockobj, test_float, 0.01, 0.02, 0.03);
}

method(TestMCRuntime, void, testArgument_double_all, xxx)
{
	debug_logt(LOG_TAG, " testArgument_double_all\n");
	ff(obj->mockobj, test_double, 0.01, 0.02, 0.03);
}

method(TestMCRuntime, void, testArgument_double_string, xxx)
{
	debug_logt(LOG_TAG, " testArgument_double_string\n");
	ff(obj->mockobj, test_double_string, 0.04, "this is a string after double");
}

method(TestMCRuntime, void, testArgument_float_string, xxx)
{
	debug_logt(LOG_TAG, " testArgument_float_string\n");
	ff(obj->mockobj, test_float_string, 0.04, "this is a string after float");
}

method(TestMCRuntime, void, testArgument_string_double, xxx)
{
	debug_logt(LOG_TAG, " testArgument_string_double\n");
	ff(obj->mockobj, test_string_double, "this is a string before double", 0.04);
}

method(TestMCRuntime, void, testArgument_string_float, xxx)
{
	debug_logt(LOG_TAG, " testArgument_string_float\n");
	ff(obj->mockobj, test_string_float, "this is a string before float", 0.04);
}

