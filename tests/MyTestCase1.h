#include "MCContext.h"
#include "MCUnitTest.h"

#ifndef _MyTestCase1 
#define _MyTestCase1 _MCUnitTestCase;\

class(MyTestCase1);

constructor(MyTestCase1, xxx);
method(MyTestCase1, testMehod1, xxx);
method(MyTestCase1, testMehod2, xxx);
method(MyTestCase1, testMehod3, xxx);
//override
method(MyTestCase1, setUp, xxx);
method(MyTestCase1, tearDown, xxx);
#endif