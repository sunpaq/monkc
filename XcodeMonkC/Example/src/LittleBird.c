//
//  Bird.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include <stdio.h>
#include "monkc.h"
#include "LittleBird.h"
#include "LittleBirdFather.h"

initer(LittleBird)
{
    obj->super = newc(mo, LittleBirdFather);
    obj->name = nil;
    return obj;
}

method(LittleBird, LittleBird*, initWithName, char* aname)
{
    obj->name = aname;
    return obj;
}

method(LittleBird, void, yourName, xxx)
{
    printf("my name is: %s\n", obj->name);
}

method(LittleBird, void, fly, xxx)
{
    printf("little bird can fly\n");
}

method(LittleBird, void, swim, xxx)
{
    printf("i can swim\n");
}

method(LittleBird, void, eat, xxx)
{
    printf("i can eat\n");
}

//implement abs
method(LittleBird, void, hello_imp, xxx)
{
    printf("little bird: hello!\n");
}

loader(LittleBird)
{
    binding(LittleBird, Bird*, initWithName, char* aname);
    binding(LittleBird, void, yourName, xxx);
    binding(LittleBird, void, fly, xxx);
    binding(LittleBird, void, swim, xxx);
    binding(LittleBird, void, eat, xxx);
    binding(LittleBird, void, hello_imp, xxx);
    return claz;
}