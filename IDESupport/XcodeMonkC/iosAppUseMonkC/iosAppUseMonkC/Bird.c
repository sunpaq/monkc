//
//  Bird.c
//  iosAppUseMonkC
//
//  Created by sun yuli on 2014/02/15.
//  Copyright (c) 2014年 sun yuli. All rights reserved.
//

#include "Bird.h"
#include "BirdFather.h"

initer(Bird){
    obj->super = newc(mo, BirdFather);
    ff(obj->super, initWithName, "a father bird");
    obj->name = NULL;
    obj->age = 29;
    return obj;
}

loader(Bird)
{
    binding(Bird, Bird*, initWithName, char* name);
    binding(Bird, int, getAge, xxx);
    binding(Bird, char*, sayHello, xxx);
    return claz;
}

method(Bird, Bird*, initWithName, char* name)
{
    obj->name = name;
    return obj;
}

method(Bird, int, getAge, xxx)
{
    return obj->age;
}

method(Bird, char*, sayHello, xxx)
{
    static char buff[1024];
    sprintf(buff, "Hello! i am %s, i was %d years old.\n", obj->name, obj->age);
    printf("%s\n", buff);
    return buff;
}
