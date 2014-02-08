//
//  BirdFather.c
//  MonkCAppXcodeTemplete
//
//  Created by sun yuli on 2014/01/13.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include <stdio.h>
#include "BirdFather.h"

initer(BirdFather)
{
    return obj;
}

method(BirdFather, int, getAge, xxx)
{
    return 29;
}

loader(BirdFather)
{
    binding(BirdFather, int, getAge, xxx);
    return claz;
}