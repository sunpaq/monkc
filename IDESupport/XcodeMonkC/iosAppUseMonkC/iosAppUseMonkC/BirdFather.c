//
//  BirdFather.c
//  iosAppUseMonkC
//
//  Created by sun yuli on 2014/02/15.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include "BirdFather.h"

initer(BirdFather){
    obj->name = NULL;
    obj->age = 92;
    return obj;
}

loader(BirdFather)
{
    binding(BirdFather, BirdFather*, initWithName, char* name);
    binding(BirdFather, int, getAge, xxx);
    binding(BirdFather, char*, sayHello, xxx);
    binding(BirdFather, char*, onlyFatherCanDo, xxx);

    return claz;
}

method(BirdFather, BirdFather*, initWithName, char* name)
{
    obj->name = name;
    return obj;
}

method(BirdFather, int, getAge, xxx)
{
    return obj->age;
}

method(BirdFather, char*, sayHello, xxx)
{
    static char buff[1024];
    sprintf(buff, "Hello! i am %s, i was %d years old.\n", obj->name, obj->age);
    printf("%s\n", buff);
    return buff;
}

method(BirdFather, char*, onlyFatherCanDo, xxx)
{
    static char buff[1024];
    sprintf(buff, "%s, i am %d years old, only i can battle with eagle\n", obj->name, obj->age);
    printf("%s\n", buff);
    return buff;
}
