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

loader(LittleBirdFather)
{
    binding(LittleBirdFather, int, getAge, xxx);
    return claz;
}