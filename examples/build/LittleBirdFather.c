//
//  BirdFather.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
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
    fh(receiver,hello_imp, 1197024991, nil);
}

method(LittleBirdFather, void, land_imp, xxx)
{
    printf("little bird father landing\n");
}

loader(LittleBirdFather)
{
    hinding(LittleBirdFather, int, getAge, 3045599689, xxx);
    hinding(LittleBirdFather, void, fly, 101491, xxx);
    hinding(LittleBirdFather, void, hello_abs, 1197016965, mo receiver);
    hinding(LittleBirdFather, void, land_imp, 2677959544, xxx);
    return claz;
}