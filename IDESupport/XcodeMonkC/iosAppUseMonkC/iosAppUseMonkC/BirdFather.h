//
//  BirdFather.h
//  iosAppUseMonkC
//
//  Created by sun yuli on 2014/02/15.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#ifndef iosAppUseMonkC_BirdFather_h
#define iosAppUseMonkC_BirdFather_h

#include "monkc.h"

monkc(BirdFather);
char* name;
int age;
end(BirdFather);

method(BirdFather, BirdFather*, initWithName, char* name);
method(BirdFather, int, getAge, xxx);
method(BirdFather, char*, sayHello, xxx);
method(BirdFather, char*, onlyFatherCanDo, xxx);


#endif
