#include "TestMCRuntime.h"
static const char* LOG_TAG = "TestMCRuntime";

constructor(TestMCRuntimeMockObj, xxx)
{
	link_class(TestMCRuntimeMockObj, MCObject, nil)
	{
		binding(TestMCRuntimeMockObj, test_double, double a, double b, double c);
		binding(TestMCRuntimeMockObj, test_float, float a, float b, float c);
		binding(TestMCRuntimeMockObj, test_double_string, double a, char* b);
		binding(TestMCRuntimeMockObj, test_float_string, float a, char* b);
		binding(TestMCRuntimeMockObj, test_string_double, char* a, double b);
		binding(TestMCRuntimeMockObj, test_string_float, char* a, float b);
	}

	return this;
}

method(TestMCRuntimeMockObj, test_double, double a, double b, double c)
{
	debug_logt(LOG_TAG, "test_double a/b/c [%f/%f/%f]\n", a,b,c);
}

method(TestMCRuntimeMockObj, test_float, float a, float b, float c)
{
	debug_logt(LOG_TAG, "test_float a/b/c [%f/%f/%f]\n", a,b,c);
}

method(TestMCRuntimeMockObj, test_double_string, double a, char* b)
{
	debug_logt(LOG_TAG, "test_float a/b/c [%f/%f/%f]\n", a,b);
}

method(TestMCRuntimeMockObj, test_float_string, float a, char* b)
{
	debug_logt(LOG_TAG, "test_float_string a/b [%f/%s]\n", a,b);
}

method(TestMCRuntimeMockObj, test_string_double, char* a, double b)
{
	debug_logt(LOG_TAG, "test_string_double a/b [%s/%f]\n", a,b);
}

method(TestMCRuntimeMockObj, test_string_float, char* a, float b)
{
	debug_logt(LOG_TAG, "test_string_float a/b [%s/%f]\n", a,b);
}

/* the test case */

constructor(TestMCRuntime, xxx)
{
	link_class(TestMCRuntime, MCUnitTestCase, nil)
	{
		binding(TestMCRuntime, testArgument_float_all, xxx);
		binding(TestMCRuntime, testArgument_double_all, xxx);
		binding(TestMCRuntime, testArgument_double_string, xxx);
		//binding(TestMCRuntime, testArgument_float_string, xxx);
		binding(TestMCRuntime, testArgument_string_double, xxx);
		binding(TestMCRuntime, testArgument_string_float, xxx);
		//override
		override(TestMCRuntime, setUp, xxx);
		override(TestMCRuntime, tearDown, xxx);
	}
	this->mockobj = nil;

	return this;
}
//override
method(TestMCRuntime, setUp, xxx)
{
	call(this, MCUnitTestCase, setUp, nil);
	this->mockobj = new(TestMCRuntimeMockObj, nil);

}

method(TestMCRuntime, tearDown, xxx)
{
	call(this, MCUnitTestCase, setUp, nil);
	relnil(this->mockobj);

}

method(TestMCRuntime, testArgument_float_all, xxx)
{
	debug_logt(LOG_TAG, " testArgument_float_all\n");
	ff(this->mockobj, test_float, 0.01, 0.02, 0.03);
}

method(TestMCRuntime, testArgument_double_all, xxx)
{
	debug_logt(LOG_TAG, " testArgument_double_all\n");
	ff(this->mockobj, test_double, 0.01, 0.02, 0.03);
}

method(TestMCRuntime, testArgument_double_string, xxx)
{
	debug_logt(LOG_TAG, " testArgument_double_string\n");
	ff(this->mockobj, test_double_string, 0.04, "this is a string after double");
}

method(TestMCRuntime, testArgument_float_string, xxx)
{
	debug_logt(LOG_TAG, " testArgument_float_string\n");
	ff(this->mockobj, test_float_string, 0.04, "this is a string after float");
}

method(TestMCRuntime, testArgument_string_double, xxx)
{
	debug_logt(LOG_TAG, " testArgument_string_double\n");
	ff(this->mockobj, test_string_double, "this is a string before double", 0.04);
}

method(TestMCRuntime, testArgument_string_float, xxx)
{
	debug_logt(LOG_TAG, " testArgument_string_float\n");
	ff(this->mockobj, test_string_float, "this is a string before float", 0.04);
}

