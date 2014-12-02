#include "monkc.h"
#include "MCUnitTest.h"

//mock object to pass argument
#ifndef TestMCRuntimeMockObj_
#define TestMCRuntimeMockObj_


monkc(TestMCRuntimeMockObj);
end(TestMCRuntimeMockObj);

method(TestMCRuntimeMockObj, void, test_double, double a, double b, double c);
method(TestMCRuntimeMockObj, void, test_float, float a, float b, float c);
method(TestMCRuntimeMockObj, void, test_double_string, double a, char* b);
method(TestMCRuntimeMockObj, void, test_float_string, float a, char* b);
method(TestMCRuntimeMockObj, void, test_string_double, char* a, double b);
method(TestMCRuntimeMockObj, void, test_string_float, char* a, float b);
#endif


#ifndef TestMCRuntime_
#define TestMCRuntime_

monkc(TestMCRuntime);
	TestMCRuntimeMockObj* mockobj;
end(TestMCRuntime);

method(TestMCRuntime, void, testArgument_float_all, xxx);
method(TestMCRuntime, void, testArgument_double_all, xxx);
method(TestMCRuntime, void, testArgument_double_string, xxx);
method(TestMCRuntime, void, testArgument_float_string, xxx);
method(TestMCRuntime, void, testArgument_string_double, xxx);
method(TestMCRuntime, void, testArgument_string_float, xxx);
//override
method(TestMCRuntime, void, setUp, xxx);
method(TestMCRuntime, void, tearDown, xxx);
#endif