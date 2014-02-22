//
//  monkcInterface.c
//  iosAppUseMonkC
//
//  Created by sun yuli on 2014/02/15.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include "Bird.h"
#include "MCString.h"
#include "MCClock.h"

char* runMonkCCode()
{
    Bird* abird = ff(new(Bird), initWithName, "a little bird");
    ff(abird, sayHello, NULL);
    return ff(abird, onlyFatherCanDo, NULL);
    
    MCString* str = ff(new(MCString), initWithCString, "a string ");
    int i;
    for (i=0; i<100; i++) {
        ff(str, add, " a piece of str\n");
    }
    
    static char buff[1024];
    ff(str, toCString, buff);
    //return buff;
    
    MCClock* clock = ff(new(MCClock), setTimeToNow, NULL);
    return ff(clock, getCurrentTimeString, NULL);
}
