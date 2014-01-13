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
    this->super = (mo)new(BirdFather);
    return this;
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
    binding(Bird, void, fly, xxx);
    binding(Bird, void, swim, xxx);
    binding(Bird, void, eat, xxx);
    return class;
}