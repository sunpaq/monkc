//
//  Bird.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2015/01/13.
//  Copyright (c) 2015年 sun yuli. All rights reserved.
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
    hinding(LittleBird, void, yourName, 3612626270, xxx);
    hinding(LittleBird, void, fly, 101491, xxx);
    hinding(LittleBird, void, swim, 3543688, xxx);
    hinding(LittleBird, void, eat, 100184, xxx);
    hinding(LittleBird, void, hello_imp, 1197024991, xxx);
    return claz;
}
