//
//  BirdFather.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include <stdio.h>
#include "LittleBirdFather.h"

initer(LittleBirdFather)
{
    return obj;
}

method(LittleBirdFather, int, getAge, xxx)
{
    return 29;
}

method(LittleBirdFather, void, fly, xxx)
{
    printf("little bird father can fly\n");
}

//abs
method(LittleBirdFather, void, hello, xxx)
{
    ff(receiver, myHello, nil);
}

loader(LittleBirdFather)
{
    binding(LittleBirdFather, int, getAge, xxx);
    binding(LittleBirdFather, void, fly, xxx);
    binding(LittleBirdFather, void, hello, xxx);
    return claz;
}