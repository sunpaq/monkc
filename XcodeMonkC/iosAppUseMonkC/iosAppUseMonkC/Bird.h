//
//  Bird.h
//  iosAppUseMonkC
//
//  Created by sun yuli on 2014/02/15.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#ifndef iosAppUseMonkC_Bird_h
#define iosAppUseMonkC_Bird_h

#include "monkc.h"

monkc(Bird);
char* name;
int age;
end(Bird);

method(Bird, Bird*, initWithName, char* name);
method(Bird, int, getAge, xxx);
method(Bird, char*, sayHello, xxx);

#endif
