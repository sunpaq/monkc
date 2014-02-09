//
//  Bird.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include <stdio.h>
#include "monkc.h"
#include "Bird.h"
#include "BirdFather.h"

initer(Bird)
{
    obj->super = newc(mo, BirdFather);
    obj->name = nil;
    return obj;
}

method(Bird, Bird*, initWithName, char* aname)
{
    obj->name = aname;
    return obj;
}

method(Bird, void, yourName, xxx)
{
    printf("my name is: %s\n", obj->name);
}

method(Bird, void, fly, xxx)
{
    printf("i can fly\n");
}

method(Bird, void, swim, xxx)
{
    printf("i can swim\n");
}

method(Bird, void, eat, xxx)
{
    printf("i can eat\n");
}

loader(Bird)
{
    binding(Bird, Bird*, initWithName, char* aname);
    binding(Bird, void, yourName, xxx);
    binding(Bird, void, fly, xxx);
    binding(Bird, void, swim, xxx);
    binding(Bird, void, eat, xxx);
    return claz;
}