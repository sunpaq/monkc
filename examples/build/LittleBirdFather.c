//
//  BirdFather.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2015/01/13.
//  Copyright (c) 2015年 sun yuli. All rights reserved.
//

#include "LittleBirdFather.h"
#include "BirdBase.h"

initer(LittleBirdFather)
{
    obj->super = newc(mo, BirdBase);
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

method(LittleBirdFather, void, hello_abs, mo receiver)
{
    ff(receiver, hello_imp, nil);
}

method(LittleBirdFather, void, land_imp, xxx)
{
    printf("little bird father landing\n");
}

loader(LittleBirdFather)
{
    binding(LittleBirdFather, int, getAge, xxx);
    binding(LittleBirdFather, void, fly, xxx);
    binding(LittleBirdFather, void, hello_abs, mo receiver);
    binding(LittleBirdFather, void, land_imp, xxx);
    return claz;
}