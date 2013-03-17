#include "MyTestCase1.h"

constructor(MyTestCase1, xxx)
{
	link_class(MyTestCase1, MCUnitTestCase, new_anony(MCUnitTestResult, nil))
	{
		have_method(MyTestCase1, testMehod1, xxx);
		have_method(MyTestCase1, testMehod2, xxx);
		have_method(MyTestCase1, testMehod3, xxx);
	}

	return this;
}

method(MyTestCase1, testMehod1, xxx)
{
	printf("test method 1\n");
}

method(MyTestCase1, testMehod2, xxx)
{
	printf("test method 2\n");
}

method(MyTestCase1, testMehod3, xxx)
{
	printf("test method 3\n");
}