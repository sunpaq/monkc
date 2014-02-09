//
//  main.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include <stdio.h>
#include "monkc.h"
#include "Bird.h"
#include "ObjCClass.h"

void testMonkC()
{
    //new a instance
    Bird* abird = new(Bird);
    
    //static call methods
    Bird_fly(abird, nil, nil);
    Bird_eat(abird, nil, nil);
    Bird_swim(abird, nil, nil);
    
    //dynamic call methods
    ff(abird, fly, nil);
    ff(abird, swim, nil);
    ff(abird, eat, nil);
    
    //dynamic call super class methods
    int fatherage = (int)ff(abird, getAge, nil);
    printf("my father age is : %d\n", fatherage);
    
    release(abird);
}

#include "MCString.h"
#include "MCClock.h"

void testLemontea()
{
    MCString* mcstr = ff(new(MCString), initWithCString, "a MCString");
    ff(mcstr, add, " the second");
    ff(mcstr, add, " the third");
    ff(mcstr, add, " the forth\n");
    ff(mcstr, print, nil);
    release(mcstr);
    
    MCClock* mcclock = ff(new(MCClock), setTimeToNow, nil);
    ff(mcclock, printTime, nil);
    ff(mcclock, printCurrentGMTTime, nil);
    release(mcclock);
}

void callFromObjC()
{
    printf("\n<call from objc class>\n\n");
    id aobj = [ObjCClass new];
    [aobj callMonkCMethod];
}

int main(int argc, const char * argv[])
{
    mc_init();//must called at very beginning
    LOG_LEVEL = MC_ERROR_ONLY;//the monkc color log system have some problem display on xcode console
        testMonkC();
        callFromObjC();
        testLemontea();
    mc_end();//must called in the end
    return 0;
}

