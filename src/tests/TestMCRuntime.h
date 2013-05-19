#include "MCContext.h"
#include "MCUnitTest.h"

//mock object to pass argument
#ifndef TestMCRuntimeMockObj_
#define TestMCRuntimeMockObj_


class(TestMCRuntimeMockObj);
end(TestMCRuntimeMockObj);

method(TestMCRuntimeMockObj, test_double, double a, double b, double c);
method(TestMCRuntimeMockObj, test_float, float a, float b, float c);
method(TestMCRuntimeMockObj, test_double_string, double a, char* b);
method(TestMCRuntimeMockObj, test_float_string, float a, char* b);
method(TestMCRuntimeMockObj, test_string_double, char* a, double b);
method(TestMCRuntimeMockObj, test_string_float, char* a, float b);
#endif


#ifndef TestMCRuntime_
#define TestMCRuntime_

class(TestMCRuntime);
	TestMCRuntimeMockObj* mockobj;
end(TestMCRuntime);

method(TestMCRuntime, testArgument_float_all, xxx);
method(TestMCRuntime, testArgument_double_all, xxx);
method(TestMCRuntime, testArgument_double_string, xxx);
method(TestMCRuntime, testArgument_float_string, xxx);
method(TestMCRuntime, testArgument_string_double, xxx);
method(TestMCRuntime, testArgument_string_float, xxx);
//override
method(TestMCRuntime, setUp, xxx);
method(TestMCRuntime, tearDown, xxx);
#endif