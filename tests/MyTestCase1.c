#include "MyTestCase1.h"

constructor(MyTestCase1, xxx)
{
	link_class(MyTestCase1, MCUnitTestCase, new_anony(MCUnitTestResult, nil))
	{
		binding(MyTestCase1, testMehod1, xxx);
		binding(MyTestCase1, testMehod2, xxx);
		binding(MyTestCase1, testMehod3, xxx);
		override(MyTestCase1, setUp, xxx);
		override(MyTestCase1, tearDown, xxx);
	}

	return this;
}

method(MyTestCase1, setUp, xxx)
{
	call(this, MCUnitTestCase, setUp, nil);
	printf("MyTestCase1 setUp\n");
}

method(MyTestCase1, tearDown, xxx)
{
	call(this, MCUnitTestCase, tearDown, nil);
	printf("MyTestCase1 tearDown\n");
}

method(MyTestCase1, testMehod1, xxx)
{
	printf("test method 1\n");
	assertYES(NO);
}

method(MyTestCase1, testMehod2, xxx)
{
	printf("test method 2\n");
	assertNotNil(nil);
}

method(MyTestCase1, testMehod3, xxx)
{
	printf("test method 3\n");
	assertEquals(0, 1);
}